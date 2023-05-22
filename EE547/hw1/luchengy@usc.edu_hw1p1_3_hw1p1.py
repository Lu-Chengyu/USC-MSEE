import sys

def factorial(num):
    result = 1
    while(num!=0):
        result *= num
        num-=1
    return result

def anagram(Input):
    repeat = 1
    counted = set()
    for letter in Input:
        if letter not in counted:
            ct = Input.count(letter, 0, len(Input))
            repeat *= factorial(ct)
            counted.add(letter)
    return str(factorial(len(Input)) // repeat)

if __name__ == "__main__":
    if len(sys.argv) < 2 or len(sys.argv[1])==0:
        sys.stdout.write("empty")
    elif sys.argv[1].lower().isalpha():
        sys.stdout.write(anagram(sys.argv[1].lower()))
    else:
        sys.stderr.write("invalid")
