# EE569 Homework Assignment #5
# Date:       April 15, 2023
# Name:     Chengyu Lu
# ID:           5157-6388-86
# email:      luchengy@usc.edu
# EE569 Homework Assignment #5 Sample Code
# requirements: python3 + pytorch
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import torch.backends.cudnn as cudnn
import torchvision as tv
import torchvision.transforms as transforms
import statistics as st
import matplotlib.pyplot as plt
import numpy as np
import math
import os

train_batch_size=256
test_batch_size=1000

class Net(nn.Module):
    def __init__(self):
        super(Net,self).__init__()
        self.conv1=nn.Conv2d(1,6,5,stride=1,padding=2)
        self.conv2=nn.Conv2d(6,16,5,stride=1,padding=0)
        self.fc1=nn.Linear(16*5*5,120)
        self.fc2=nn.Linear(120,84)
        self.fc3=nn.Linear(84,10)
    def forward(self,x):
        x=F.max_pool2d(F.relu(self.conv1(x)),2)
        x=F.max_pool2d(F.relu(self.conv2(x)),2)
        x=x.view(-1,self.num_flat_features(x))
        x=F.relu(self.fc1(x))
        x=F.relu(self.fc2(x))
        x=self.fc3(x)
        return x
    def num_flat_features(self,x):
        #x is a 4D tensor
        x_size=x.size()[1:]
        num=1
        for n in x_size:
            num*=n
        return num

def load_data():
    transform=transforms.Compose(
        [transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))])
    train_set=tv.datasets.FashionMNIST(
        root='./data',
        train=True,
        download=True,
        transform=transform
        )
    # noiseConfusionMatrix(train_set, 0.5)
    train_set = add_noise(train_set, 0.8) #0.5, 0, 0.2, 0.4, 0.6, and 0.8

    train_loader=torch.utils.data.DataLoader(
        train_set,
        batch_size=train_batch_size,
        shuffle=True,
        num_workers=10)
    test_set=tv.datasets.FashionMNIST(
        root='./data',
        train=False,
        download=True,
        transform=transform
        )
    test_loader=torch.utils.data.DataLoader(
        test_set,
        batch_size=test_batch_size,
        shuffle=False,
        num_workers=10)
    print("data loaded successfully...")
    return train_loader,test_loader

def noiseConfusionMatrix(dataset, error_rate=0.5):
    confusion_matrix = np.zeros([10, 10])
    total = [0] * 10
    labels = dataset.targets
    for i in range(len(labels)):
        total[labels[i]] += 1
        ori_labels = int(labels[i])
        if np.random.rand(1) > (1 - error_rate):
            whole_label = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
            whole_label.remove(labels[i])
            labels[i] = whole_label[np.random.randint(0, 9)]
        confusion_matrix[labels[i], ori_labels] += 1
    for i in range(np.size(confusion_matrix, 0)):
        for j in range(np.size(confusion_matrix, 1)):
            confusion_matrix[i][j] = confusion_matrix[i][j] / total[i]
    print(confusion_matrix)

def add_noise(dataset, error_rate):

    labels = dataset.targets
    for i in range(len(labels)):
        if np.random.rand(1) > (1 - error_rate):
            whole_label = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
            whole_label.remove(labels[i])
            labels[i] = whole_label[np.random.randint(0, 9)]
    dataset.targets = labels
    return dataset

def accuracy(model,x,neg=False):
    with torch.no_grad():
        correct=0
        total=0
        class_correct = list(0. for i in range(10))
        class_total = list(0. for i in range(10))
        for data in x:
            images,labels=data
            
            if neg:
            	images=-images
            # images,labels=images, labels
            images, labels = images.cuda(), labels.cuda()# added
            outputs=model(images)
            _,predicted=torch.max(outputs.data,1)
            total+=labels.size(0)
            correct+=(predicted==labels).sum().item()
            
        return (100 * correct / total)

def confusionMatrix(model, x, neg=False):
    with torch.no_grad():
        confusionMatrix = np.zeros([10, 10])
        total = [0] * 10
        class_correct = list(0. for i in range(10))
        class_total = list(0. for i in range(10))
        for data in x:
            images, labels = data
            if neg:
                images = -images
            images, labels = images.cuda(), labels.cuda()
            outputs = model(images)
            _, predicted = torch.max(outputs.data, 1)
            for i in range(len(labels)):
                total[labels[i]] += 1
                confusionMatrix[labels[i]][predicted[i]] += 1
                # if(labels[i]!=predicted[i]):
                #     transforms.ToPILImage()(images[i]).show()
        for i in range(np.size(confusionMatrix, 0)):
            for j in range(np.size(confusionMatrix, 1)):
                confusionMatrix[i][j] = confusionMatrix[i][j] / total[i]
    fig, ax = plt.subplots()
    im = ax.imshow(confusionMatrix, cmap = "Blues")
    ax.figure.colorbar(im)
    for i in range(len(confusionMatrix)):
        for j in range(len(confusionMatrix[i])):
            ax.text(j, i, np.round_(confusionMatrix[i][j], decimals=2), fontsize=9, verticalalignment="center", horizontalalignment="center")
    ax.xaxis.set_major_locator(plt.MultipleLocator(1))
    ax.yaxis.set_major_locator(plt.MultipleLocator(1))
    ax.set_xlabel('Predicted value')
    ax.set_ylabel('Actual value')
    plt.show()

def train(train_loader, test_loader, model, criterion, optimizer,epoch):
    model.train()
    running_loss=0
    for i,data in enumerate(train_loader,0):
        inputs,labels=data
        # inputs,labels=inputs, labels
        inputs, labels = inputs.cuda(), labels.cuda()
        optimizer.zero_grad()
        outputs=net(inputs)
        loss=criterion(outputs,labels)
        loss.backward()
        optimizer.step()

        # print statistics
        running_loss+=loss.item()
        if i%200==199:
            print("[epoch %d, iter %5d] loss: %.3f"%(epoch+1,i+1,running_loss/200))
            running_loss=0.0
    train_acc=accuracy(model,train_loader)
    test_acc=accuracy(model,test_loader)
    print("epoch %d: train_acc %.3f, test_acc %.3f"%(epoch+1,train_acc,test_acc))
    return train_acc,test_acc

def display(train_acc,test_acc):
    fig,ax=plt.subplots()
    ax.plot(range(1,len(train_acc)+1),train_acc,color='r',label='train_acc')
    ax.plot(range(1,len(test_acc)+1),test_acc,color='b',label='test_acc')
    ax.legend(loc='lower right')
    ax.set_xlabel('epoch')
    ax.set_ylabel('Accuracy(%)')
    plt.show()

if __name__ == '__main__':
    train_loader,test_loader=load_data()
    testing_accuracies = [0]*5
    # net=Net()
    device = torch.device("cuda", 0)
    # new model
    for i in range(5):
        net = Net()
        net = net.to(device)
        print('*****Now start run#'+str(i)+'*****')
        # training
        learning_rate = 0.023
        momentum = 0.9
        decay = 0.001
        max_epoch = 20
        criterion = nn.CrossEntropyLoss()
        optimizer = optim.SGD(net.parameters(), lr=learning_rate, momentum=momentum, weight_decay=decay)
        train_acc = []
        test_acc = []
        for epoch in range(max_epoch):
            train_acc_t, test_acc_t = train(train_loader, test_loader, net, criterion, optimizer, epoch)
            train_acc.append(train_acc_t)
            test_acc.append(test_acc_t)
            # if test_acc[len(test_acc)-1] >= 99:
            #     break
        display(train_acc, test_acc)
        testing_accuracies[i] = test_acc[-1]
        confusionMatrix(net, test_loader)
    print("Final testing accuracy: %.3f, standard deviation: %.3f" % (st.mean(testing_accuracies), st.stdev(testing_accuracies)))



