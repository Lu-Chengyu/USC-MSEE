import huffman

f = open('SandFtext.txt','r') # SandFaudio.txt, SandFbinary.txt, SandFimage.txt, SandFtext.txt
list = f.readlines()
print(list)
symboldict = {}
codebookInput = []
for b in list:
    if b!='\n':
        Sy, Fr = b.split(" Freq: ")
        if Sy == '':
            codebookInput.append(('\n', int(Fr)))
            symboldict['\n']=int(Fr)
        else:
            codebookInput.append((Sy, int(Fr)))
            symboldict[Sy]=int(Fr)
print(codebookInput)    
t1 = huffman.codebook(codebookInput)
print(t1)
shortest = 999
longest =0
compressedFileSize=0.0
Bavg = 0.0
for key, value in t1.items():
    if len(value) > longest:
        longest = len(value)
    if len(value) < shortest:
        shortest = len(value)
    compressedFileSize += symboldict[key] * len(value)
    Bavg += symboldict[key] * len(value)/65536.0
    
print(shortest)
print(longest)
print(compressedFileSize/8.0)
print(Bavg)
