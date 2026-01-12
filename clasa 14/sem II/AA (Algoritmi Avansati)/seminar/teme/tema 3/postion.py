def determinant(a, b, c):
    return a[0] * b[1] + b[0] * c[1] + c[0] * a[1] - c[0] * b[1] - a[0] * c[1] - b[0] * a[1]

nrPoints = int(input())

for i in range(nrPoints):
    line = input().strip().split(" ")

    x1 = float(line[0])
    y1 = float(line[1])
    a = (x1, y1)

    x2 = float(line[2])
    y2 = float(line[3])
    b = (x2, y2)

    x3 = float(line[4])
    y3 = float(line[5])
    c = (x3, y3)

    if determinant(a, b, c) == 0:
        print("TOUCH")
    elif determinant(a, b, c) > 0:
        print("LEFT")
    else:
        print("RIGHT")

   