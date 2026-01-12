nrPoints = int(input())
points = []
nrLeft = 0
nrLine = 0
nrRight = 0

for i in range(nrPoints):
    line = input().strip().split(" ")

    x = float(line[0])
    y = float(line[1])

    points.append((x, y))


def determinant(a, b, c):
    return a[0] * b[1] + b[0] * c[1] + c[0] * a[1] - c[0] * b[1] - a[0] * c[1] - b[0] * a[1]


for index in range(len(points) - 2):
    if determinant(points[index], points[index + 1], points[index + 2]) < 0:
        nrRight += 1
    elif determinant(points[index], points[index + 1], points[index + 2]) == 0:
        nrLine += 1
    else:
        nrLeft += 1

if determinant(points[len(points) - 2], points[len(points) - 1], points[0]) < 0:
    nrRight += 1
elif determinant(points[len(points) - 2], points[len(points) - 1], points[0]) == 0:
    nrLine += 1
else:
    nrLeft += 1


print(nrLeft, nrRight, nrLine)