import math

def primes(n):
    """ Returns  a list of primes < n """
    sieve = [True] * n
    for i in range(3,int(n**0.5)+1,2):
        if sieve[i]:
            sieve[i*i::2*i]=[False]*((n-i*i-1)//(2*i)+1)
    return [2] + [i for i in range(3,n,2) if sieve[i]]

MAX = 100000
num = 47
primesBeforeNum = primes(num + 1)
pair = 0
nonPair = 0
nth = 10
nthWithoutStart = nth + len(primesBeforeNum)
estimateNthWithoutStart = math.ceil(nthWithoutStart*math.log(nthWithoutStart) + nthWithoutStart*math.log(math.log(nthWithoutStart)))
res = primes(estimateNthWithoutStart)[len(primesBeforeNum):nthWithoutStart]
print(res)