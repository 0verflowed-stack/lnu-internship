inputData = input().split(" ")
x = float(inputData[0])
n = int(inputData[1])
sum = 0
sumElement = 1
for i in range(0, n):
    sum += (-1)**i * x**i * sumElement
    print(f"{i+1}: {sum}")
    sumElement *= (5 + 2 * i) / (2 + 2 * i)
print(f"Suma=:{sum}")