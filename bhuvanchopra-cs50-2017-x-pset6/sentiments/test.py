import sys,os

text='hate'
positives = os.path.join(sys.path[0], "positive-words.txt")
negatives = os.path.join(sys.path[0], "negative-words.txt")
l=[]
for word in text:
    if word in positives:
        l.append(1)
    elif word in negatives:
        l.append(-1)
    else:
        l.append(0)
print( sum(l))