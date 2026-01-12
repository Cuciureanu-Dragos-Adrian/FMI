import pygame
import sys
import math


def distEuclid(p0, p1):
    (x0, y0) = p0
    (x1, y1) = p1
    return math.sqrt((x0 - x1) ** 2 + (y0 - y1) ** 2)


class Graph:
    noduri = [
        (0, 0), (0, 1), (0, 2), (0, 3), (0, 4),
        (1, 0), (1, 1), (1, 2), (1, 3), (1, 4),
        (2, 0), (2, 1), (2, 2), (2, 3), (2, 4),
        (3, 0), (3, 1), (3, 2), (3, 3), (3, 4),
        (4, 0), (4, 1), (4, 2), (4, 3), (4, 4)
    ]
    muchii = [(0, 1), (1, 2), (2, 3), (3, 4), # linii verticale
              (5, 6), (6, 7), (7, 8), (8, 9),
              (10, 11), (11, 12), (12, 13), (13, 14),
              (15, 16), (16, 17), (17, 18), (18, 19),
              (20, 21), (21, 22), (22, 23), (23, 24),
              (0, 5), (5, 10), (10, 15), (15, 20), # linii orizontale
              (1, 6), (6, 11), (11, 16), (16, 21),
              (2, 7), (7, 12), (12, 17), (17, 22),
              (3, 8), (8, 13), (13, 18), (18, 23),
              (4, 9), (9, 14), (14, 19), (19, 24),
              (0, 6), (6, 10), (10, 16), (16, 20), # linii diagonale
              (2, 6), (6, 12), (12, 16), (16, 22),
              (2, 8), (8, 12), (12, 18), (18, 22),
              (4, 8), (8, 14), (14, 18), (18, 24)
    ]
    scalare = 100
    translatie = 20
    razaPct = 10
    razaPiesa = 20


pygame.init()
culoareEcran = (255, 255, 255)
culoareLinii = (0, 0, 0)

ecran = pygame.display.set_mode(size=(500, 500))

piesaAlba = pygame.image.load('piesa-alba.png')
diametruPiesa = 2 * Graph.razaPiesa
piesaAlba = pygame.transform.scale(piesaAlba, (diametruPiesa, diametruPiesa))
piesaNeagra = pygame.image.load('piesa-neagra.png')
piesaNeagra = pygame.transform.scale(piesaNeagra, (diametruPiesa, diametruPiesa))
piesaSelectata = pygame.image.load('piesa-rosie.png')
piesaSelectata = pygame.transform.scale(piesaSelectata, (diametruPiesa, diametruPiesa))
nodPiesaSelectata = False
coordonateNoduri = [[Graph.translatie + Graph.scalare * x for x in nod] for nod in Graph.noduri]
pieseAlbe = [
    coordonateNoduri[3], coordonateNoduri[4],
    coordonateNoduri[8], coordonateNoduri[9],
    coordonateNoduri[13], coordonateNoduri[14],
    coordonateNoduri[17], coordonateNoduri[18], coordonateNoduri[19],
    coordonateNoduri[22], coordonateNoduri[23], coordonateNoduri[24]
]
nodPiesaSelectata = None
pieseNegre = [
    coordonateNoduri[0], coordonateNoduri[1], coordonateNoduri[2],
    coordonateNoduri[5], coordonateNoduri[6], coordonateNoduri[7],
    coordonateNoduri[10], coordonateNoduri[11],
    coordonateNoduri[15],coordonateNoduri[16],
    coordonateNoduri[20], coordonateNoduri[21]
]


def deseneazaEcranJoc():
    ecran.fill(culoareEcran)
    for nod in coordonateNoduri:
        pygame.draw.circle(surface=ecran, color=culoareLinii, center=nod, radius=Graph.razaPct,
                           width=0)  # width=0 face un cerc plin

    for muchie in Graph.muchii:
        p0 = coordonateNoduri[muchie[0]]
        p1 = coordonateNoduri[muchie[1]]
        pygame.draw.line(surface=ecran, color=culoareLinii, start_pos=p0, end_pos=p1, width=5)
    for nod in pieseAlbe:
        ecran.blit(piesaAlba, (nod[0] - Graph.razaPiesa, nod[1] - Graph.razaPiesa))
    for nod in pieseNegre:
        ecran.blit(piesaNeagra, (nod[0] - Graph.razaPiesa, nod[1] - Graph.razaPiesa))
    if nodPiesaSelectata:
        ecran.blit(piesaSelectata, (nodPiesaSelectata[0] - Graph.razaPiesa, nodPiesaSelectata[1] - Graph.razaPiesa))
    pygame.display.update()


deseneazaEcranJoc()
rand = 0


def pot_muta(piesa):
    index = coordonateNoduri.index(piesa)
    for i in [index-6, index-5, index-4, index-1, index+1, index+4, index+5, index+6]:
        if 0 <= i < 25:
            loc = coordonateNoduri[i]
            if (index, i) in Graph.muchii or (i, index) in Graph.muchii:
                return loc not in pieseAdverse + pieseCurente
    return False

def final():

    if len(pieseCurente) == 0:
        print("Ai pierdut! Nu mai are piese")
        return True
    if len(pieseAdverse) == 0:
        print("Ai castigat! Nu mai are piese")
        return True
    ok = False
    for piesa in pieseCurente:
        if pot_muta(piesa):
            ok = True
            print(ok)
            break
    if not ok:
        print("Ai pierdut! Nu mai ai unde muta!")
        return True
    ok = False
    for piesa in pieseAdverse:
        if pot_muta(piesa):
            ok = True
            print(ok)
            break
    if not ok:
        print("Ai castigat! Nu mai are unde muta!")
        return True





def coliniare (n0, n1):
    x = n0[0]
    y = n0[1]
    x1 = n1[0]
    y1 = n1[1]
    if x == x1 and abs(y-y1) == 200:
        y2 = abs(y+y1)/2
        return [x, y2]
    if y == y1 and abs(x-x1) == 200:
        x2 = abs(x+x1)/2
        return [x2, y]
    if abs(x-x1) == 200 and abs(y-y1) == 200:
        x2 = abs(x+x1)/2
        y2 = abs(y+y1)/2
        return [x2, y2]
    return False


def capturare(n0, n1):
    n2 = coliniare(n0, n1)
    if n2 == False:
        return False
    if n1 not in pieseAdverse and n2 in pieseAdverse:
        return n2
    return False


print("Muta " + ("negru" if rand else "alb"))
while True:
    for ev in pygame.event.get():
        if ev.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if ev.type == pygame.MOUSEBUTTONDOWN:
            pos = pygame.mouse.get_pos()
            for nod in coordonateNoduri:
                if distEuclid(pos, nod) <= Graph.razaPct:
                    if rand == 1:
                        piesa = piesaNeagra
                        pieseCurente = pieseNegre
                        pieseAdverse = pieseAlbe
                    else:
                        piesa = piesaAlba
                        pieseCurente = pieseAlbe
                        pieseAdverse = pieseNegre
                    if nod not in pieseAlbe + pieseNegre:
                        if nodPiesaSelectata:
                            n0 = coordonateNoduri.index(nod)
                            n1 = coordonateNoduri.index(nodPiesaSelectata)
                            piesa_capturata = capturare(nod, nodPiesaSelectata)
                            if piesa_capturata:
                                pieseAdverse.remove(piesa_capturata)
                                pieseCurente.remove(nodPiesaSelectata)
                                pieseCurente.append(nod)
                                rand = 1 - rand
                                print("Muta " + ("negru" if rand else "alb"))
                                nodPiesaSelectata = False
                                if final():
                                    aa = 1
                                #     exit()
                            elif ((n0, n1) in Graph.muchii or (n1, n0) in Graph.muchii):
                                pieseCurente.remove(nodPiesaSelectata)
                                pieseCurente.append(nod)
                                rand = 1 - rand
                                print("Muta " + ("negru" if rand else "alb"))
                                nodPiesaSelectata = False
                                if final():
                                    aa = 1
                                #     exit()
                    else:
                        if nod in pieseCurente:
                            if nodPiesaSelectata == nod:
                                nodPiesaSelectata = False
                            else:
                                nodPiesaSelectata = nod

                    deseneazaEcranJoc()
                    break
