nrPoints = int(input())
points = []

for i in range(nrPoints):
    line = input().strip().split(" ")

    x = float(line[0])
    y = float(line[1])

    points.append((x, y))


nrConvexPoints = int(input())
convexPoints = []

for i in range(nrConvexPoints):
    line = input().strip().split(" ")

    x = float(line[0])
    y = float(line[1])

    convexPoints.append((x, y))


def determinant(a, b, c):
    return a[0] * b[1] + b[0] * c[1] + c[0] * a[1] - c[0] * b[1] - a[0] * c[1] - b[0] * a[1]


def determinePositionConvexPoint(points, convexPoint):
    outside = False
    margin = False

    for index in range(len(points) - 1):
        if determinant(points[index], points[index + 1], convexPoint) < 0:
            outside = True
        elif determinant(points[index], points[index + 1], convexPoint) == 0:
            margin = True

    if determinant(points[len(points) - 1], points[0], convexPoint) < 0:
        outside = True
    elif determinant(points[len(points) - 1], points[0], convexPoint) == 0:
        margin = True

    if outside == True:
        print("OUTSIDE")
    elif margin == True:
        print("BOUNDARY")
    else:
        print("INSIDE")


for convexPoint in convexPoints:
    determinePositionConvexPoint(points, convexPoint)
