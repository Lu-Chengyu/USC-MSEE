import math


i=0
codebook=[]
codebookformap = {}
f = open('text.txt','r') # audio.txt, binary.txt, image.txt, text.txt
list = f.readlines()
for line in list:
    if line !='\n':
        i+=1
        var0, var1, var2 = line.split("sep,")
        if var0 == '':
            codebookformap['\n']= var2.strip()
        else:
            codebookformap[var0]= var2.strip()

with open('text.dat','r') as f: # audio.dat, binary.dat, image.dat, text.dat
    ff=f.read()
f.close()
#print(ff)
encodedFile = open('encodedText.txt',mode = 'w') # encodedAudio.txt, encodedBinary.txt, encodedImage.txt, encodedText.txt
for byt in ff:
    encodedFile.write(codebookformap[byt])
encodedFile.close()


