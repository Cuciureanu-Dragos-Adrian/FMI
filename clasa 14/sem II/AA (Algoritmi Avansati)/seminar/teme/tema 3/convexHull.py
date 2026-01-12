nrPoints = int(input())

points = []
errorMargin = 0.00001

for i in range(nrPoints):
    line = input().strip().split(" ")

    x = int(line[0])
    y = int(line[1])

    points.append((x, y))


def determinant(a, b, c):
    return a[0] * b[1] + b[0] * c[1] + c[0] * a[1] - c[0] * b[1] - a[0] * c[1] - b[0] * a[1]


def cmp(arr):
    return arr[0], arr[1]


def getConvexHull(arr):
    stack = [arr[0], arr[1]]

    for index in range(2, len(arr)):
        point = arr[index]
        while len(stack) > 1 and determinant(stack[-2], stack[-1], point) < errorMargin:
            stack.pop()
        stack.append(point)

    return stack


points.sort(key=cmp)
lowerConvexHull = getConvexHull(points)

reversedPoints = points[::-1]
upperConvexHull = getConvexHull(reversedPoints)

convexHull = lowerConvexHull

for i in range(1, len(upperConvexHull) - 1):
    convexHull.append(upperConvexHull[i])

print(f"{len(convexHull)}")
for elem in convexHull:
    print(f"{elem[0]} {elem[1]}")

