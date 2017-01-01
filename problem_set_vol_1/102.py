# UVA question 102
# 

import itertools
permutations = itertools.permutations;

import sys
stdin = sys.stdin

def retainBin( bin, retain ):
    if retain == 'B':
        return int(bin[1]) + int(bin[2])
    elif retain == 'G':
        return int(bin[0]) + int(bin[2])
    elif retain == 'C':
        return int(bin[0]) + int(bin[1]) 
    return 0

# Function to calculate moves needed for one solution
def solution( bin, order ):
    sum = 0
    sum += retainBin(bin[0:3], order[0])
    sum += retainBin(bin[3:6], order[1])
    sum += retainBin(bin[6:9], order[2])
    return sum


# Read input
for line in stdin:
    input = line.split()
    minSeq = "XXX";
    minCnt = pow(2, 32);
    for i in itertools.permutations("BGC", 3):
        r = solution(input, i)
        if r < minCnt:
            minCnt = r
            minSeq = i
        if r == minCnt and minSeq > i:
            minSeq = i
    print( "".join(minSeq), minCnt)


