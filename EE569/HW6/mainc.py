# EE569 Homework Assignment #6
# Date:       May 1, 2023
# Name:     Chengyu Lu
# ID:           5157-6388-86
# email:      luchengy@usc.edu
import numpy as np
from tensorflow.keras.datasets import mnist,fashion_mnist
from skimage.util import view_as_windows
from pixelhop import Pixelhop
from skimage.measure import block_reduce
import xgboost as xgb
import warnings, gc
import time
from sklearn.metrics import accuracy_score, confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt

np.random.seed(1)

# Preprocess
N_Train_Reduced = 10000    # 10000
N_Train_Full = 60000     # 50000
N_Test = 10000            # 10000

BS = 2000 # batch size


def shuffle_data(X, y):
    shuffle_idx = np.random.permutation(y.size)
    X = X[shuffle_idx]
    y = y[shuffle_idx]
    return X, y


def select_balanced_subset(images, labels, use_num_images):
    '''
    select equal number of images from each classes
    '''
    num_total, H, W, C = images.shape
    num_class = np.unique(labels).size
    num_per_class = int(use_num_images / num_class)

    # Shuffle
    images, labels = shuffle_data(images, labels)

    selected_images = np.zeros((use_num_images, H, W, C))
    selected_labels = np.zeros(use_num_images)

    for i in range(num_class):
        selected_images[i * num_per_class:(i + 1) * num_per_class] = images[labels == i][:num_per_class]
        selected_labels[i * num_per_class:(i + 1) * num_per_class] = np.ones((num_per_class)) * i

    # Shuffle again
    selected_images, selected_labels = shuffle_data(selected_images, selected_labels)

    return selected_images, selected_labels

def Shrink(X, shrinkArg):
    #---- max pooling----
    pool = shrinkArg['pool']
    # TODO: fill in the rest of max pooling
    X = block_reduce(X, (1, pool, pool, 1), np.max)
    #---- neighborhood construction
    win = shrinkArg['win']
    stride = shrinkArg['stride']
    pad = shrinkArg['pad']
    ch = X.shape[-1]
    # TODO: fill in the rest of neighborhood construction
    if pad > 0:
        X = np.pad(X, ((0, 0), (pad, pad), (pad, pad), (0, 0)), "reflect")
    X = view_as_windows(X, (1, win, win, ch), (1, stride, stride, ch))
    return X.reshape(X.shape[0], X.shape[1], X.shape[2], -1)

# example callback function for how to concate features from different hops
def Concat(X, concatArg):
    return X

def get_feat(X, num_layers=3):
    output = p2.transform_singleHop(X,layer=0)
    if num_layers>1:
        for i in range(num_layers-1):
            output = p2.transform_singleHop(output, layer=i+1)
    return output


if __name__ == "__main__":
    warnings.filterwarnings("ignore")
    # ---------- Load MNIST data and split ----------
    (x_train, y_train), (x_test,y_test) = mnist.load_data()
    # (x_train, y_train), (x_test,y_test) = fashion_mnist.load_data()

    # -----------Data Preprocessing-----------
    x_train = np.asarray(x_train,dtype='float32')[:,:,:,np.newaxis]
    x_test = np.asarray(x_test,dtype='float32')[:,:,:,np.newaxis]
    y_train = np.asarray(y_train,dtype='int')
    y_test = np.asarray(y_test,dtype='int')

    # if use only 10000 images train pixelhop
    x_train_reduced, y_train_reduced = select_balanced_subset(x_train, y_train, use_num_images=N_Train_Reduced)

    x_train /= 255.0
    x_test /= 255.0


    # -----------Module 1: set PixelHop parameters-----------
    # TODO: fill in this part
    SaabArgs = [{"num_AC_kernels": -1, "needBias": False, "cw": False},
                {'num_AC_kernels': -1, 'needBias': True, 'cw': True}, # False
                {'num_AC_kernels': -1, 'needBias': True, 'cw': True}] # False
    shrinkArgs = [{"func": Shrink, "win": 5, "stride": 1, "pad": 2, "pool": 1},
                  {"func": Shrink, "win": 5, "stride": 1, "pad": 0, "pool": 2},
                  {"func": Shrink, "win": 5, "stride": 1, "pad": 0, "pool": 2}]
    concatArg = {"func": Concat}

    # -----------Module 1: Train PixelHop -----------
    # TODO: fill in this part
    trainingStart = time.time()
    # p2 = Pixelhop(depth=3, TH1=0.002, TH2=0.001, SaabArgs=SaabArgs, shrinkArgs=shrinkArgs, concatArg=concatArg).fit(x_train)
    p2 = Pixelhop(depth=3, TH1=0.005, TH2=0.001, SaabArgs=SaabArgs, shrinkArgs=shrinkArgs, concatArg=concatArg).fit(x_train)
    # p2 = Pixelhop(depth=3, TH1=0.01, TH2=0.001, SaabArgs=SaabArgs, shrinkArgs=shrinkArgs, concatArg=concatArg).fit(x_train)

    # --------- Module 2: get only Hop 3 feature for both training set and testing set -----------
    # you can get feature "batch wise" and concatenate them if your memory is restricted
    # TODO: fill in this part
    # train_hop1_feats = get_feat(x_train, num_layers = 0)
    # print(train_hop1_feats.shape)
    # train_hop2_feats = get_feat(x_train, num_layers = 2)
    # print(train_hop2_feats.shape)
    train_hop3_feats = get_feat(x_train)
    # print(train_hop3_feats.shape)
    train_hop3_feats = train_hop3_feats.reshape(train_hop3_feats.shape[0], -1)

    print(f"Training time: {(time.time()-trainingStart)/60} minutes")

    test_hop3_feats = get_feat(x_test)
    test_hop3_feats = test_hop3_feats.reshape(test_hop3_feats.shape[0], -1)

    # --------- Module 2: standardization
    STD = np.std(train_hop3_feats, axis=0, keepdims=1)
    train_hop3_feats = train_hop3_feats/STD
    test_hop3_feats = test_hop3_feats/STD
    
    #---------- Module 3: Train XGBoost classifier on hop3 feature ---------

    tr_acc = []
    te_acc = []
    
    clf = xgb.XGBClassifier(n_jobs=-1,
                        objective='multi:softprob',
                        # tree_method='gpu_hist', gpu_id=None,
                        max_depth=6,n_estimators=100,
                        min_child_weight=5,gamma=5,
                        subsample=0.8,learning_rate=0.1,
                        nthread=8,colsample_bytree=1.0)

    # TODO: fill in the rest and report accuracy
    clf.fit(train_hop3_feats, y_train)
    trainingAccuracy = accuracy_score(y_train, clf.predict(train_hop3_feats))
    y_prediction = clf.predict(test_hop3_feats)
    testingAccuracy = accuracy_score(y_test, y_prediction)
    print(f"Training Accuracy: {trainingAccuracy}, Testing Accuracy: {testingAccuracy}")
    
    fig = plt.figure()
    ax = fig.add_subplot()
    confusionMatrix = confusion_matrix(y_test, y_prediction)
    confusionMatrix = confusionMatrix/confusionMatrix.astype(np.float64).sum(axis=0)*100
    ConfusionMatrixDisplay(confusion_matrix=confusionMatrix, display_labels=['0','1','2','3','4','5','6','7','8','9']).plot(ax=ax)
    ax.set_title("Confusion Matrix(%)")
    ax.set_xlabel("Predicted Label")
    ax.set_ylabel("True Label")
    fig.tight_layout()
    fig.savefig(f'MNIST.png')
    # fig.savefig(f'FashionMNIST.png')