import math

def primes(n):
    """ Returns  a list of primes < n """
    sieve = [True] * n
    for i in range(3,int(n**0.5)+1,2):
        if sieve[i]:
            sieve[i*i::2*i]=[False]*((n-i*i-1)//(2*i)+1)
    return [2] + [i for i in range(3,n,2) if sieve[i]]

def notPair(number):
    if number == 0:
        return False
    pair = 0
    while number != 0:
        if number % 2 == 0:
            pair += 1
        number = int(number/10)
    return pair == 0

filtered = lambda x: [x[i] for i in range(0, len(x)) if notPair(x[i])]

def getNumbersAfter(nNumsAfter, primesBeforeNumber):
    nthWithoutStart = nNumsAfter + len(primesBeforeNumber)
    estimateNthWithoutStart = math.ceil(nthWithoutStart*math.log(nthWithoutStart) + nthWithoutStart*math.log(math.log(nthWithoutStart)))
    return primes(estimateNthWithoutStart)[len(primesBeforeNumber):nthWithoutStart]

num = 47
nth = 10

primesBeforeNum = primes(num + 1)

result = []
nthTemp = nth
while True:
    result = filtered(getNumbersAfter(nthTemp, primesBeforeNum))
    if (len(result) < nth):
        nthTemp += 20
    else:
        result = result[0:nth+1]
        break

print(result)