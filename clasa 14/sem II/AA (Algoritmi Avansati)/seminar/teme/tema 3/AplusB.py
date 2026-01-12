nrPoints = int(input())

for i in range(nrPoints):
    line = input().strip().split(" ")

    x = int(line[0])
    y = int(line[1])

    print(x + y)