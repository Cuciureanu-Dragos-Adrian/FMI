nrPlanes = int(input())
planes = []

for i in range(nrPlanes):
    line = input().split()

    a = int(line[0])
    b = int(line[1])
    c = int(line[2])

    planes.append((a, b, c))


def intersection_planes(planes):
    min_x, min_y = -1e7, -1e7
    max_x, max_y = 1e7, 1e7

    for plane in planes:
        minim = -1e7
        maxim = 1e7

        a = int(plane[0])
        b = int(plane[1])
        c = int(plane[2])

        if a == 0:
            if b > 0:
                maxim = - c/b
            else:
                minim = - c/b
        else:
            if a > 0:
                maxim = - c/a
            else:
                minim = - c/a

        if a == 0:
            min_y = max(min_y, minim)
            max_y = min(max_y, maxim)
        else:
            min_x = max(min_x, minim)
            max_x = min(max_x, maxim)

    if min_x > max_x or min_y > max_y:
        print("VOID")
    elif min_x != -1e7 and min_y != -1e7 and max_x != 1e7 and max_y != 1e7:
        print("BOUNDED")
    else:
        print("UNBOUNDED")


intersection_planes(planes)