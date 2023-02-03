import math


i=0
codebook=[]
with open("text.txt") as fh: # audio.txt, binary.txt, image.txt, text.txt
    for line in fh:
        i+=1
        var0, var1, var3, var2 = line.split(",")
        codebook.append(var1)
        codebook.append(var2)
print(i)
filesize=0.0
bpa =0.0
entro = 0.0                         
for b in range(1,i+1): #number of lilne in code book text.file: 63
    entro += (float(codebook[2*b-2])/65536.0)*math.log((65536.0/ (float(codebook[2*b-2]))),2.0)
    bpa +=  (float(codebook[2*b-2])/65536.0)*(len(codebook[2*b-1])-1)
    filesize+=(len(codebook[2*b-1])-1)*int(codebook[2*b-2])
    

print(filesize/8.0)
print(entro)
print(bpa)



