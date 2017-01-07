import sys
from math import gcd
from math import sqrt

mgcd = gcd

squares = dict()
isquares = dict()
for i in range(0,1000000):
    squares[i] = i**2
    isquares[i**2] = i

for nstr in sys.stdin:
    n = int(nstr)
    numTriples = 0
    numSet = set()

    for y in range(2, n):
        limit = int(sqrt(squares[n] - squares[y]))
        for x in range(1, min(y, limit)+1):
            lhs = squares[x] + squares[y]
            if lhs in isquares:
                z = isquares[lhs]
                numSet.add(x)
                numSet.add(y)
                numSet.add(z)
                if ((mgcd(x,y) == 1) 
                    and (mgcd(x,z)==1) 
                    and (mgcd(y,z)==1)):
                    numTriples+=1;
#                    print( (x, y, z))
    p = n - len(numSet)
    print(numTriples, p)


