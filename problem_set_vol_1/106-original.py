import sys
from math import gcd

dictgcd = dict()

def mgcd(x,y):
    if not (x,y) in dictgcd:
        dictgcd[(x,y)] = gcd(x,y)
    return dictgcd[(x,y)]

for nstr in sys.stdin:
    n = int(nstr)
    numTriples = 0
    numSet = set()
    allTuples = []
    for z in range(3, n+1):
        for y in range(2, z):
            for x in range(1, y):
                if (((x**2) + (y**2) == (z**2))): 
                    numSet.add(x)
                    numSet.add(y)
                    numSet.add(z)
                    allTuples += [ (x, y, z) ]
                    if ((mgcd(x,y) == 1) 
                        and (mgcd(x,z)==1) 
                        and (mgcd(y,z)==1)):
                        numTriples+=1;
    for i in sorted(allTuples):
        print(i)
    p = n - len(numSet)
    print(numTriples, p)


