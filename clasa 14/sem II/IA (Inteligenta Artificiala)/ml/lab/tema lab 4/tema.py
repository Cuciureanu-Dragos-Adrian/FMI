def functie(t, s, n):
    if len(t) < n or len(s) < n:
        return -1

    dict = {}
    nrnGrameComune = 0

    for i in range(len(t) - n):
        cuv = t[i : i + n]
        if cuv not in dict:
            dict[cuv] = True

    for i in range(len(s) - n):
        cuv = s[i : i + n]
        if cuv in dict:
            nrnGrameComune += 1

    return nrnGrameComune

cuv1 = 'ananas copt'
cuv2 = 'banana verde'
p = 4

rez = functie(cuv1, cuv2, p)
print(f"functia a returnat {rez} {p}-grame")
