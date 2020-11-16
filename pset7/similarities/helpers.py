from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    linesA = set(a.splitlines())
    linesB = set(b.splitlines())
    
    # & operator copies a bit to the result if it exists in both operands
    return linesA & linesB


def sentences(a, b):
    """Return sentences in both a and b"""

    sentencesA = set(sent_tokenize(a))
    sentencesB = set(sent_tokenize(b))
    
    return sentencesA & sentencesB


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    subA = []
    subB = []

    for i in range(len(a) - n + 1):
        subA.append(a[i:i + n])
        
    for i in range(len(b) - n + 1):
        subB.append(b[i:i + n])   
        
    return set(subA) & set(subB)
