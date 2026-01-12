import math
import sys


def determinant(a, b, c):
    return a[0] * b[1] + b[0] * c[1] + c[0] * a[1] - c[0] * b[1] - a[0] * c[1] - b[0] * a[1]


def cmp(arr):
    return arr[0], arr[1]


def getConvexHull(arr):
    stack = [arr[0], arr[1]]

    for index in range(2, len(arr)):
        point = arr[index]
        while len(stack) > 1 and determinant(stack[-2], stack[-1], point) <= 0:
            stack.pop()
        stack.append(point)

    return stack


# step 1
def firstPart(points):
    points.sort(key=cmp)
    lowerConvexHull = getConvexHull(points)

    reversedPoints = points[::-1]
    upperConvexHull = getConvexHull(reversedPoints)

    convexHull = lowerConvexHull

    for i in range(1, len(upperConvexHull) - 1):
        convexHull.append(upperConvexHull[i])

    return convexHull


# step 2
def secondPart(points, tsp):
    edgePoints = {}

    for node in points:
        if node not in tsp:
            minn = 100000
            pair = None

            for i in range(len(tsp)):
                j = 0

                if i == len(tsp) - 1:
                    j = 0
                else:
                    j = i + 1

                p1 = tsp[i]
                p2 = tsp[j]

                if math.dist(p1, node) + math.dist(node, p2) - math.dist(p1, p2) < minn:
                    minn = math.dist(p1, node) + math.dist(node, p2) - math.dist(p1, p2)
                    pair = (i, j)

            if pair not in edgePoints.keys():
                edgePoints[pair] = [node]
            else:
                edgePoints[pair].append(node)

    return edgePoints


# step 3 and 4
def thirdPart(edgePoints, tsp):
    arr = []

    for pair in edgePoints.keys():
        minn = 100000
        nod_minn = None

        for node in edgePoints[pair]:
            rapport = (math.dist(tsp[pair[0]], node) + math.dist(node, tsp[pair[1]])) / math.dist(tsp[pair[0]], tsp[pair[1]])

            if rapport < minn:
                minn = rapport
                nod_minn = node

        arr.append((pair[0] + 1, nod_minn))

    arr.sort(key=lambda x: x[0])

    nrInserted = 0

    for elem in arr:
        tsp.insert(elem[0] + nrInserted, elem[1])
        nrInserted += 1

    return tsp


def TSPFinder():
    nrPoints = int(input())

    points = []

    for i in range(nrPoints):
        line = input().strip().split(" ")

        x = int(line[0])
        y = int(line[1])

        points.append((x, y))

    tsp = firstPart(points)

    # step 5
    while len(tsp) < len(points):
        edgePoints = secondPart(points, tsp)
        tsp = thirdPart(edgePoints, tsp)

    index = 0

    for i in range(1, len(tsp)):
        if tsp[i][0] < tsp[index][0]:
            index = i

    for i in range(index, len(tsp)):
        print(f"{tsp[i][0]} {tsp[i][1]}")

    for i in range(index):
        print(f"{tsp[i][0]} {tsp[i][1]}")

    print(f"{tsp[index][0]} {tsp[index][1]}")


TSPFinder()