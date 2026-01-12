nrPlanes = int(input())
planes = []

for i in range(nrPlanes):
    line = input().split()

    a = int(line[0])
    b = int(line[1])
    c = int(line[2])

    planes.append((a, b, c))


nrPoints = int(input())
points = []

for i in range(nrPoints):
    point = input().split()

    x = float(point[0])
    y = float(point[1])

    min_x, min_y = -10000000, -10000000
    max_x, max_y = 10000000, 10000000

    for plane in planes:
        a = plane[0]
        b = plane[1]
        c = plane[2]

        if a * x + b * y + c >= 0:
            continue

        minim = -10000000
        maxim = 10000000

        if a == 0:
            if b > 0:
                maxim = - c/b
                max_y = min(max_y, maxim)
            else:
                minim = - c/b
                min_y = max(min_y, minim)
        else:
            if a > 0:
                maxim = - c/a
                max_x = min(max_x, maxim)
            else:
                minim = - c/a
                min_x = max(min_x, minim)
            
    if min_x == -10000000 or min_y == -10000000 or max_x == 10000000 or max_y == 10000000:
        print("NO")
    else:
        area = (max_y - min_y) * (max_x - min_x)
        
        print("YES")
        print(round(area, 6))