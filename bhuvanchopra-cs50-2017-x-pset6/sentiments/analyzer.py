import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        l1=[]
        l2=[]
        f1=open(positives,'r')
        f2=open(negatives,'r')
        for line in f1.readlines():
            if not line.startswith(';'):
                l1.append(str.strip(line))
            #else:
                #l1.append(str.strip(line))
        
        for line in f2.readlines():
            if not line.startswith(';'):
                l2.append(str.strip(line))
            #else:
                #l2.append(str.strip(line))
        
        self.positives=l1
        self.negatives=l2
        

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        l=[]
        t=nltk.tokenize.TweetTokenizer()
        text1=t.tokenize(text=str.lower(text))
        for word in text1:
            if word in self.positives:
                l.append(1)
            elif word in self.negatives:
                l.append(-1)
            else:
                l.append(0)
        return sum(l)
        
