# Notes:
# Already followig sample solution from Algorithmist
# plus some things that we don't do in python to increase speed
# but python is too slow to make the 3s limit
#

import sys
from math import gcd
from math import sqrt

mgcd = gcd

sqrs = [i**2 for i in range(0, 1000001)]

for nstr in sys.stdin:
    n = int(nstr)
    numTriples = 0

    nsqrt = int(sqrt(n))
    numSet = [ False for i in range(0,n+1)]
    for r in range(1, nsqrt+1):
        rsq = sqrs[r]
        up = min((n-rsq), r-1)
        for s in range(1, up+1):
            ssq = sqrs[s]
            x = (rsq - ssq)
            y = (2 * r * s) 
            z = (rsq + ssq) 
            
            if z <= n and sqrs[x] + sqrs[y] == sqrs[z] :
                k = 1
                while k * z <=n:
                    numSet[k*x] = True
                    numSet[k*y] = True
                    numSet[k*z] = True
                    k+= 1
                
                if (mgcd(x,y) == 1): 
                    numTriples+=1;
    count = 0;
    for i in range(1, n+1):
        if numSet[i]:
            count += 1
    
    p = n - count 
    print(numTriples, p)


