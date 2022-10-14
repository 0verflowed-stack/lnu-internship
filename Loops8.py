inputData = input().split(" ")
x = float(inputData[0])
n = int(inputData[1])
sum = 0
sumElement = 2 * 2 * 3 / 3
for i in range(1, n+1):
    sum += sumElement
    print(f"{i}: {sum}")
    sumElement *= - ((i+1)*(2*i+2)*(2*i+3)*(4*i*i-1)*x*x) / (i*(4*(i+1)**2-1))
print(f"Suma=:{sum}")