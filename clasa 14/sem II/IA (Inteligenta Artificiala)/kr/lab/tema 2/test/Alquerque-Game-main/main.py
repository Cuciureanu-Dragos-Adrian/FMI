import time
import pygame
import sys
import math
import statistics

def distEuclid(p0, p1):
    (x0, y0) = p0
    (x1, y1) = p1
    return math.sqrt((x0 - x1) ** 2 + (y0 - y1) ** 2)

class Joc:
    """
    Clasa care defineste jocul. Se va schimba de la un joc la altul.
    """
    JMIN = None
    JMAX = None
    GOL = '#'
    noduri = [
        (0, 0), (0, 1), (0, 2), (0, 3), (0, 4),
        (1, 0), (1, 1), (1, 2), (1, 3), (1, 4),
        (2, 0), (2, 1), (2, 2), (2, 3), (2, 4),
        (3, 0), (3, 1), (3, 2), (3, 3), (3, 4),
        (4, 0), (4, 1), (4, 2), (4, 3), (4, 4)
    ]
    muchii = [(0, 1), (1, 2), (2, 3), (3, 4),  # linii verticale
                  (5, 6), (6, 7), (7, 8), (8, 9),
                  (10, 11), (11, 12), (12, 13), (13, 14),
                  (15, 16), (16, 17), (17, 18), (18, 19),
                  (20, 21), (21, 22), (22, 23), (23, 24),
                  (0, 5), (5, 10), (10, 15), (15, 20),  # linii orizontale
                  (1, 6), (6, 11), (11, 16), (16, 21),
                  (2, 7), (7, 12), (12, 17), (17, 22),
                  (3, 8), (8, 13), (13, 18), (18, 23),
                  (4, 9), (9, 14), (14, 19), (19, 24),
                  (0, 6), (6, 10), (10, 16), (16, 20),  # linii diagonale
                  (2, 6), (6, 12), (12, 16), (16, 22),
                  (2, 8), (8, 12), (12, 18), (18, 22),
                  (4, 8), (8, 14), (14, 18), (18, 24)
    ]
    scalare = 120
    translatie = 60
    raza_pct = 20
    raza_piesa = 50

    @classmethod
    def initializeaza(cls, display):
        cls.display = display
        cls.diametru_piesa = 2 * cls.raza_piesa
        cls.piesa_alba = pygame.image.load('resources/piesa-alba.png')
        cls.piesa_alba = pygame.transform.scale(cls.piesa_alba, (cls.diametru_piesa, cls.diametru_piesa))
        cls.piesa_neagra = pygame.image.load('resources/piesa-neagra.png')
        cls.piesa_neagra = pygame.transform.scale(cls.piesa_neagra, (cls.diametru_piesa, cls.diametru_piesa))
        cls.piesa_rosie = pygame.image.load('resources/piesa-rosie.png')
        cls.piesa_rosie = pygame.transform.scale(cls.piesa_rosie, (cls.diametru_piesa, cls.diametru_piesa))

        cls.culoare_ecran = (190, 190, 190)
        cls.culoare_linii = (70, 70, 70)
        cls.coordonate_noduri = [[cls.translatie + cls.scalare * x for x in nod] for nod in cls.noduri]

    def deseneaza_grid(self, marcaj=None):  # tabla de exemplu este ["#","x","#","0",......]
        self.display.fill(self.culoare_ecran)
        for nod in self.coordonate_noduri:
            pygame.draw.circle(surface=self.display, color=self.culoare_linii, center=nod, radius=self.raza_pct,
                               width=0)  # width=0 face un cerc plin

        for muchie in self.muchii:
            p0 = self.coordonate_noduri[muchie[0]]
            p1 = self.coordonate_noduri[muchie[1]]
            pygame.draw.line(surface=self.display, color=self.culoare_linii, start_pos=p0, end_pos=p1, width=5)
        for nod in self.piese_albe:
            self.display.blit(self.piesa_alba, (nod[0] - self.raza_piesa, nod[1] - self.raza_piesa))
        for nod in self.piese_negre:
            self.display.blit(self.piesa_neagra, (nod[0] - self.raza_piesa, nod[1] - self.raza_piesa))
        if self.nod_piesa_selectata:
            self.display.blit(self.piesa_rosie, (self.nod_piesa_selectata[0] - self.raza_piesa, self.nod_piesa_selectata[1] - self.raza_piesa))
        pygame.display.flip()  # obligatoriu pentru a actualiza interfata (desenul)

    # pygame.display.update()

    def __init__(self, piese_albe=None, piese_negre=None, capturat = False, nod_piesa_selectata = None):
        self.capturat = capturat
        self.coordonate_noduri = [[self.translatie + self.scalare * x for x in nod] for nod in self.noduri]
        self.nod_piesa_selectata = nod_piesa_selectata

        if piese_albe is None:
            self.piese_albe = [
            self.coordonate_noduri[3], self.coordonate_noduri[4],
            self.coordonate_noduri[8], self.coordonate_noduri[9],
            self.coordonate_noduri[13], self.coordonate_noduri[14],
            self.coordonate_noduri[17], self.coordonate_noduri[18], self.coordonate_noduri[19],
            self.coordonate_noduri[22], self.coordonate_noduri[23], self.coordonate_noduri[24]
        ]
        else:
            self.piese_albe = piese_albe

        if piese_negre is None:
            self.piese_negre = [
            self.coordonate_noduri[0], self.coordonate_noduri[1], self.coordonate_noduri[2],
            self.coordonate_noduri[5], self.coordonate_noduri[6], self.coordonate_noduri[7],
            self.coordonate_noduri[10], self.coordonate_noduri[11],
            self.coordonate_noduri[15], self.coordonate_noduri[16],
            self.coordonate_noduri[20], self.coordonate_noduri[21]
        ]
        else:
            self.piese_negre = piese_negre

    @classmethod
    def jucator_opus(cls, jucator):
        return cls.JMAX if jucator == cls.JMIN else cls.JMIN

    def pot_muta(self, piesa, jucator):
        # daca pot muta pe vecini
        index = self.coordonate_noduri.index(piesa)
        for i in [index - 6, index - 5, index - 4, index - 1, index + 1, index + 4, index + 5, index + 6]:
            if 0 <= i < 25:
                loc = self.coordonate_noduri[i]
                if (index, i) in self.muchii or (i, index) in self.muchii:
                    if loc not in self.piese_albe + self.piese_negre:
                        return True

        piese_curente = list(self.piese_albe)
        piese_adverse = list(self.piese_negre)
        if jucator == 'negre':
            piese_curente, piese_adverse = piese_adverse, piese_curente
        # daca pot sari undeva
        for i in [-12, -10, -8, -2, 2, 8, 10, 12]:
            mij = int(index + i / 2)
            varf = index + i
            if 0 <= mij < 25 and 0 <= varf < 25 and self.e_muchie(index, mij) and self.e_muchie(mij, varf):
                if self.coordonate_noduri[mij] in piese_adverse and self.coordonate_noduri[
                    varf] not in piese_adverse + piese_curente:
                    return True
        return False

    def final(self):
        # daca cineva nu mai are piese
        if len(self.piese_albe) == 0:
            return "negre"
        if len(self.piese_negre) == 0:
            return "albe"
        # daca cineva nu mai are unde muta
        ok = False
        for piesa in self.piese_albe:
            if self.pot_muta(piesa, "albe"):
                ok = True
                break
        if not ok:
            return "negre"
        ok = False
        for piesa in self.piese_negre:
            if self.pot_muta(piesa, "negre"):
                ok = True
                break
        if not ok:
            return "albe"
        return False

    def e_muchie(self, index1, index2):
        return (index1, index2) in self.muchii or (index2, index1) in self.muchii

    def mutari(self, jucator_opus):
        # primele mutari pe care le verific sunt capturarile deoarece sunt obligat sa le fac
        l_mutari = []
        piese_curente = self.piese_albe # notarea noua
        piese_adverse = self.piese_negre
        if jucator_opus == 'negre':
            piese_curente, piese_adverse = piese_adverse, piese_curente
        pot_captura = False
        for piesa in piese_curente: # pentru fiecare piesa
            index = self.coordonate_noduri.index(piesa) # am preluat indexul din lista
            for i in [-12, -10, -8, -2, 2, 8, 10, 12]: # pentru fiecare nod pe care pot SA SAR
                mij = int(index + i/2) # am calculat vecinul peste care trec
                varf = index + i # am calculat nodul pe care sar
                if 0 <= mij < 25 and 0 <= varf < 25 and self.e_muchie(index, mij) and self.e_muchie(mij, varf):
                    if self.coordonate_noduri[mij] in piese_adverse and self.coordonate_noduri[varf] not in piese_adverse + piese_curente:
                        # daca inca sunt in matricea jocului cu mijlocul si varful si am muchii intre ele
                        # daca pe vecinul peste care trec are o piese adversa
                        # si daca nodul pe care sar este gol
                        piese_curente_noi = list(piese_curente) # am modificat piesele curente(mutat piesa)
                        piese_curente_noi.remove(piesa)
                        piese_curente_noi.append(self.coordonate_noduri[varf])
                        piese_adverse_noi = list(piese_adverse)
                        piese_adverse_noi.remove(self.coordonate_noduri[mij]) # am sters piesa peste care am sarit
                        pot_captura = True # variabila ce indica faptul ca am avut cel putin o capturare
                        if self.JMAX == 'negre': # am adaugat la lista de mutari
                            l_mutari.append(Joc(piese_adverse_noi, piese_curente_noi, True))
                        else:
                            l_mutari.append(Joc(piese_curente_noi, piese_adverse_noi, True))
        if pot_captura: # daca am avut capturari returnez lista curenta
            return l_mutari
        # daca nu, verific unde pot muta in vecini
        for piesa in piese_curente: # pentru fiecare piesa
            index = self.coordonate_noduri.index(piesa) # am preluat indexul din lista
            for i in [index - 6, index - 5, index - 4, index - 1, index + 1, index + 4, index + 5, index + 6]: # pentru fiecare nod pe care pot SA MUT
                if 0 <= i < 25: # daca inca sunt in matircea jocului
                    loc = self.coordonate_noduri[i] # am luat nodul unde o sa mut
                    if self.e_muchie(i, index): # daca am muchie intre cele 2 noduri
                        if loc not in piese_curente + piese_adverse: # daca nodul nou este gol
                            piese_curente_noi = list(piese_curente)
                            piese_curente_noi.remove(piesa) # am modificat piesele curente(mutat piesa)
                            piese_curente_noi.append(loc)
                            if self.JMAX == 'negre': # am adaugat la lista de mutari
                                l_mutari.append(Joc(piese_adverse, piese_curente_noi))
                            else:
                                l_mutari.append(Joc(piese_curente_noi, piese_adverse))
        return l_mutari

    # linie deschisa inseamna linie pe care jucatorul mai poate forma o configuratie castigatoare
    # practic e o linie fara simboluri ale jucatorului opus

    def linie_deschisa(self, piesa, jucator):
        # functie care intoarce numarul de capturari pe care le pot face cu o piesa
        scor = 0
        index = self.coordonate_noduri.index(piesa)
        piese_curente = self.piese_negre
        piese_adverse = self.piese_albe
        if jucator == 'albe':
            piese_curente, piese_adverse = piese_adverse, piese_curente
        for i in [-12, -10, -8, -2, 2, 8, 10, 12]:
            mij = int(index + i/2)
            varf = index + i
            if 0 <= mij < 25 and 0 <= varf < 25 and self.e_muchie(index, mij) and self.e_muchie(mij, varf):
                if self.coordonate_noduri[mij] in piese_adverse and self.coordonate_noduri[varf] not in piese_adverse + piese_curente:
                    scor += 1
        return scor

    def capturari(self, jucator, mod):
        scor = 0
        if mod == '1':
            # cate piese pot captura in starea curenta
            # pentru fiecare piesa adaug maxim 1
            # acest scor este prielnic lui MAX deoarece cu cat captureaza mai multe piese cu atat sansele adversarului de castig scad
            if jucator == 'negre':
                for piesa in self.piese_negre:
                    if self.linie_deschisa(piesa, jucator):
                        scor += 1
            else:
                for piesa in self.piese_albe:
                    if self.linie_deschisa(piesa, jucator):
                        scor += 1
        else:
            # cate piese pot captura in starea curenta
            # pentru fiecare piesa calculez maximul de capturari
            # acest scor este prielnic lui MAX deoarece cu cat captureaza mai multe piese cu atat sansele adversarului de castig scad
            if jucator == 'negre':
                for piesa in self.piese_negre:
                    nr_capt = self.linie_deschisa(piesa, jucator)
                    if nr_capt > scor:
                        scor = nr_capt
            else:
                for piesa in self.piese_albe:
                    nr_capt = self.linie_deschisa(piesa, jucator)
                    if nr_capt > scor:
                        scor = nr_capt
        return scor

    def estimeaza_scor(self, adancime, mod='1'):
        t_final = self.final() # verific daca e final
        if t_final == self.__class__.JMAX: # daca castiga PC
            return (99 + adancime)
        elif t_final == self.__class__.JMIN: # daca castiga jucatorul
            return (-99 - adancime)
        else: # altfel scor pc - scor jucator
            return self.capturari(self.__class__.JMAX, mod) - self.capturari(self.__class__.JMIN, mod)

    def __str__(self):
        sir = ""
        endl = 0
        for lin in range(5):
            for col in range(0,21,5):
                x = self.coordonate_noduri[col+lin]
                endl += 1
                if x in self.piese_negre:
                    sir += "N"
                elif x in self.piese_albe:
                    sir += "A"
                else:
                    sir += "G"
                if endl % 5 == 0:
                    sir += "\n"
        return sir


class Stare:
    """
    Clasa folosita de algoritmii minimax si alpha-beta
    Are ca proprietate tabla de joc
    Functioneaza cu conditia ca in cadrul clasei Joc sa fie definiti JMIN si JMAX (cei doi jucatori posibili)
    De asemenea cere ca in clasa Joc sa fie definita si o metoda numita mutari() care ofera lista cu configuratiile posibile in urma mutarii unui jucator
    """

    def __init__(self, tabla_joc, j_curent, adancime, parinte=None, estimare=None):
        self.tabla_joc = tabla_joc
        self.j_curent = j_curent

        # adancimea in arborele de stari
        self.adancime = adancime

        # estimarea favorabilitatii starii (daca e finala) sau al celei mai bune stari-fiice (pentru jucatorul curent)
        self.estimare = estimare

        # lista de mutari posibile din starea curenta
        self.mutari_posibile = []

        # cea mai buna mutare din lista de mutari posibile pentru jucatorul curent
        self.stare_aleasa = None

    def mutari(self):
        l_mutari = self.tabla_joc.mutari(self.j_curent)
        juc_opus = Joc.jucator_opus(self.j_curent)
        l_stari_mutari = [Stare(mutare, juc_opus, self.adancime - 1, parinte=self) for mutare in l_mutari]

        return l_stari_mutari

    def __str__(self):
        sir = str(self.tabla_joc)
        return sir


""" Algoritmul MinMax """


def min_max(stare, mod_estimare):
    global n_min, n_max, n_l, mutari_gen  # noduri
    if stare.adancime == 0 or stare.tabla_joc.final():
        stare.estimare = stare.tabla_joc.estimeaza_scor(stare.adancime, mod_estimare)
        return stare

    # calculez toate mutarile posibile din starea curenta
    stare.mutari_posibile = stare.mutari()
    mutari_gen += len(stare.mutari_posibile)


    # aplic algoritmul minimax pe toate mutarile posibile (calculand astfel subarborii lor)
    mutariCuEstimare = [min_max(mutare, mod_estimare) for mutare in stare.mutari_posibile]

    if stare.j_curent == Joc.JMAX:
        # daca jucatorul e JMAX aleg starea-fiica cu estimarea maxima
        stare.stare_aleasa = max(mutariCuEstimare, key=lambda x: x.estimare)
    else:
        # daca jucatorul e JMIN aleg starea-fiica cu estimarea minima
        stare.stare_aleasa = min(mutariCuEstimare, key=lambda x: x.estimare)
    stare.estimare = stare.stare_aleasa.estimare
    return stare


def alpha_beta(alpha, beta, stare, mod_estimare):
    global n_min, n_max, n_l, mutari_gen  # noduri
    if stare.adancime == 0 or stare.tabla_joc.final():
        stare.estimare = stare.tabla_joc.estimeaza_scor(stare.adancime, mod_estimare)
        return stare
    if alpha > beta:
        return stare  # este intr-un interval invalid deci nu o mai procesez
    stare.mutari_posibile = stare.mutari()
    mutari_gen += len(stare.mutari_posibile)

    if stare.j_curent == Joc.JMAX:
        estimare_curenta = float('-inf')
        stare.mutari_posibile = sorted(stare.mutari_posibile, key=lambda x: x.tabla_joc.estimeaza_scor(stare.adancime), reverse=True)
        # pentru sortarea dupa scorul estimat
        for mutare in stare.mutari_posibile:
            # calculeaza estimarea pentru starea noua, realizand subarborele
            stare_noua = alpha_beta(alpha, beta, mutare, mod_estimare)
            if (estimare_curenta < stare_noua.estimare):
                stare.stare_aleasa = stare_noua
                estimare_curenta = stare_noua.estimare
            if (alpha < stare_noua.estimare):
                alpha = stare_noua.estimare
                if alpha >= beta:
                    break
    elif stare.j_curent == Joc.JMIN:
        estimare_curenta = float('inf')
        stare.mutari_posibile = sorted(stare.mutari_posibile,key=lambda x : x.tabla_joc.estimeaza_scor(stare.adancime))
        # pentru sortarea dupa scorul estimat
        for mutare in stare.mutari_posibile:
            stare_noua = alpha_beta(alpha, beta, mutare, mod_estimare)
            if (estimare_curenta > stare_noua.estimare):
                stare.stare_aleasa = stare_noua
                estimare_curenta = stare_noua.estimare
            if (beta > stare_noua.estimare):
                beta = stare_noua.estimare
                if alpha >= beta:
                    break
    stare.estimare = stare.stare_aleasa.estimare
    return stare


def afis():
    global t_l, n_l, timp_total, mutari_juc, mutari_pc
    if len(t_l):
        print("Timpul minim de gandire al calculatorului: " + str(min(t_l)) + " milisecunde")
        print("Timpul maxim de gandire al calculatorului: " + str(max(t_l)) + " milisecunde")
        print("Timpul mediu de gandire al calculatorului: " + str(sum(t_l) / len(t_l)) + " milisecunde")
        print("Timpul median de gandire al calculatorului: " + str(statistics.median(t_l)) + " milisecunde\n")
    if len(n_l):
        print("Numarul minim de mutari generate: " + str(min(n_l)))
        print("Numarul maxim de mutari generate: " + str(max(n_l)))
        print("Numarul mediu de mutari generate: " + str(sum(n_l) / len(n_l)))
        print("Numarul median de mutari generate: " + str(statistics.median(n_l)) + "\n")

    timp = int(round(time.time())) - timp_total
    print("Timpul total jucat: " + str(timp) + " secunde")
    print("Jucatorul a facut " + str(mutari_juc) + " mutari")
    print("Calculatorul a facut " + str(mutari_pc) + " mutari")
    return True


def afis_daca_final(stare_curenta):
    global game_over
    if stare_curenta == "force quit":
        print("\nProgramul a fost intrerupt!\n")
        if not game_over:
            return afis()
    else:
        final = stare_curenta.tabla_joc.final()
        if (final):
            game_over = True
            print("\nA castigat jucatorul cu piesele " + final + "!!\n")
            # colorare simboluri castigatoare
            if final == 'albe':
                for piesa in stare_curenta.tabla_joc.piese_albe:
                    Joc.display.blit(Joc.piesa_rosie, (piesa[0] - Joc.raza_piesa, piesa[1] - Joc.raza_piesa))
                pygame.display.update()
            elif final == 'negre':
                for piesa in stare_curenta.tabla_joc.piese_negre:
                    Joc.display.blit(Joc.piesa_rosie, (piesa[0] - Joc.raza_piesa, piesa[1] - Joc.raza_piesa))
                pygame.display.update()
            return afis()

    return False


def coliniare (n0, n1): # calcularea "mijlocului"
    x = n0[0]
    y = n0[1]
    x1 = n1[0]
    y1 = n1[1]
    if x == x1 and abs(y-y1) == 240:
        y2 = abs(y+y1)/2
        return [x, y2]
    if y == y1 and abs(x-x1) == 240:
        x2 = abs(x+x1)/2
        return [x2, y]
    if abs(x-x1) == 240 and abs(y-y1) == 240:
        x2 = abs(x+x1)/2
        y2 = abs(y+y1)/2
        return [x2, y2]
    return False


def capturare(n0, n1, piese_adverse): # functie pentru a vedea daca jucatorul a capturat o piesa
    n2 = coliniare(n0, n1) # calcularea "mijlocului" dintre n0 si n1
    if n2 == False: # daca nu estes corect
        return False
    if n1 not in piese_adverse and n2 in piese_adverse: # daca n1 e gol si n2 e piesa adversa
        return n2
    return False


def puteam_captura(stare_curenta, JMIN):
    piese_curente, piese_adverse = stare_curenta.tabla_joc.piese_albe, stare_curenta.tabla_joc.piese_negre
    if JMIN == "negre":
        piese_curente, piese_adverse = piese_adverse, piese_curente
    l = []
    for piesa in piese_curente:
        index = stare_curenta.tabla_joc.coordonate_noduri.index(piesa)
        for i in [-12, -10, -8, -2, 2, 8, 10, 12]:
            mij = int(index + i/2)
            varf = index + i
            if 0 <= mij < 25 and 0 <= varf < 25 and stare_curenta.tabla_joc.e_muchie(index, mij) and \
                    stare_curenta.tabla_joc.e_muchie(mij, varf):
                if stare_curenta.tabla_joc.coordonate_noduri[mij] in piese_adverse and \
                        stare_curenta.tabla_joc.coordonate_noduri[varf] not in piese_adverse + piese_curente:
                    l.append(piesa)
                    break
    return l


class Buton:
    def __init__(self, display=None, left=0, top=0, w=0, h=0, culoareFundal=(53, 80, 115),
                 culoareFundalSel=(89, 134, 194), text="", font="arial", fontDimensiune=25, culoareText=(255, 255, 255),
                 valoare=""):
        self.display = display
        self.culoareFundal = culoareFundal
        self.culoareFundalSel = culoareFundalSel
        self.text = text
        self.font = font
        self.w = w
        self.h = h
        self.selectat = False
        self.fontDimensiune = fontDimensiune
        self.culoareText = culoareText
        # creez obiectul font
        fontObj = pygame.font.SysFont(self.font, self.fontDimensiune)
        self.textRandat = fontObj.render(self.text, True, self.culoareText)
        self.dreptunghi = pygame.Rect(left, top, w, h)
        # aici centram textul
        self.dreptunghiText = self.textRandat.get_rect(center=self.dreptunghi.center)
        self.valoare = valoare

    def selecteaza(self, sel):
        self.selectat = sel
        self.deseneaza()

    def selecteazaDupacoord(self, coord):
        if self.dreptunghi.collidepoint(coord):
            self.selecteaza(True)
            return True
        return False

    def updateDreptunghi(self):
        self.dreptunghi.left = self.left
        self.dreptunghi.top = self.top
        self.dreptunghiText = self.textRandat.get_rect(center=self.dreptunghi.center)

    def deseneaza(self):
        culoareF = self.culoareFundalSel if self.selectat else self.culoareFundal
        pygame.draw.rect(self.display, culoareF, self.dreptunghi)
        self.display.blit(self.textRandat, self.dreptunghiText)


class GrupButoane:
    def __init__(self, listaButoane=[], indiceSelectat=0, spatiuButoane=10, left=0, top=0):
        self.listaButoane = listaButoane
        self.indiceSelectat = indiceSelectat
        self.listaButoane[self.indiceSelectat].selectat = True
        self.top = top
        self.left = left
        leftCurent = self.left
        for b in self.listaButoane:
            b.top = self.top
            b.left = leftCurent
            b.updateDreptunghi()
            leftCurent += (spatiuButoane + b.w)

    def selecteazaDupacoord(self, coord):
        for ib, b in enumerate(self.listaButoane):
            if b.selecteazaDupacoord(coord):
                self.listaButoane[self.indiceSelectat].selecteaza(False)
                self.indiceSelectat = ib
                return True
        return False

    def deseneaza(self):
        # atentie, nu face wrap
        for b in self.listaButoane:
            b.deseneaza()

    def getValoare(self):
        ok = False
        for btn in self.listaButoane:
            if btn.selectat:
                ok = True
                break
        if not ok:
            return ok
        return self.listaButoane[self.indiceSelectat].valoare


############# ecran initial ########################
def deseneaza_alegeri(display, tabla_curenta):
    btn_alg = GrupButoane(
        top=20,
        left=50,
        listaButoane=[
            Buton(display=display, w=110, h=50, text="minimax", valoare="minimax"),
            Buton(display=display, w=110, h=50, text="alphabeta", valoare="alphabeta")
        ],
        spatiuButoane=30,
        indiceSelectat=1)
    btn_juc = GrupButoane(
        top=120,
        left=50,
        listaButoane=[
            Buton(display=display, w=110, h=50, text="albe", valoare="albe"),
            Buton(display=display, w=110, h=50, text="negre", valoare="negre")
        ],
        spatiuButoane=30,
        indiceSelectat=0)
    btn_incep = GrupButoane(
        top=220,
        left=50,
        listaButoane=[
            Buton(display=display, w=110, h=50, text="Incep EU", valoare="eu"),
            Buton(display=display, w=110, h=50, text="Incepe PC", valoare="pc")
        ],
        spatiuButoane=30,
        indiceSelectat=0)
    btn_dif = GrupButoane(
        top = 320,
        left = 50,
        listaButoane=[
            Buton(display=display, w=110, h=50, text="Incepator", valoare="2"),
            Buton(display=display, w=110, h=50, text="Mediu", valoare="3"),
            Buton(display=display, w=110, h=50, text="Avansat", valoare="4")
        ],
        spatiuButoane=30,
        indiceSelectat= 2
    )
    btn_estimari = GrupButoane(
        top=420,
        left=50,
        listaButoane=[
            Buton(display=display, w=110, h=50, text="Estimare 1", valoare="1"),
            Buton(display=display, w=110, h=50, text="Estimare 2", valoare="2")
        ],
        spatiuButoane=30,
        indiceSelectat=1
    )

    ok = Buton(display=display, top=520, left=50, w=110, h=50, text="ok", culoareFundal=(155, 0, 55))
    btn_alg.deseneaza()
    btn_juc.deseneaza()
    btn_dif.deseneaza()
    btn_incep.deseneaza()
    btn_estimari.deseneaza()
    ok.deseneaza()
    while True:
        for ev in pygame.event.get():
            if ev.type == pygame.QUIT:
                afis_daca_final("force quit")
                pygame.quit()
                sys.exit()
            elif ev.type == pygame.MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()
                if not btn_alg.selecteazaDupacoord(pos):
                    if not btn_juc.selecteazaDupacoord(pos):
                        if not btn_incep.selecteazaDupacoord(pos):
                            if not btn_dif.selecteazaDupacoord(pos):
                                if not btn_estimari.selecteazaDupacoord(pos):
                                    if ok.selecteazaDupacoord(pos):
                                        if btn_juc.getValoare() and btn_alg.getValoare() and btn_incep.getValoare() and btn_dif.getValoare() and btn_estimari.getValoare():
                                            display.fill((0, 0, 0))  # stergere ecran
                                            tabla_curenta.deseneaza_grid()
                                            return btn_juc.getValoare(), btn_alg.getValoare(), btn_incep.getValoare(), btn_dif.getValoare(), btn_estimari.getValoare()
                                        else:
                                            print("Trebuie selectata cel putin o valoare de pe fiecare rand!")
        pygame.display.update()


def main():
    # initializari variabile globale pentru timp, mutari si noduri

    global t_juc_inainte, t_l, n_l, timp_total, mutari_pc, mutari_juc, mutari_gen, game_over
    t_juc_inainte = int(round(time.time() * 1000)) # timpul de start pentru muatrile jucatorului
    t_l = [] # lista cu timpi
    n_l = [] # lista cu numere de noduri
    timp_total = int(round(time.time())) # timpul la care a pornit programul
    mutari_pc = mutari_juc = mutari_gen = 0 # variabile pentru numarul de mutari
    l_puteam_captura = []
    game_over = False # variabila pentru a nu afisa de 2 ori

    # initializare tabla
    tabla_curenta = Joc();
    print("Tabla initiala")
    print(str(tabla_curenta))

    # setari interf grafica
    pygame.init()
    pygame.display.set_caption('Richiteanu Mihai-Sebastian - Alquerque')
    # dimensiunea ferestrei in pixeli
    ecran = pygame.display.set_mode(size=(599, 599))  # N *100+ N-1
    Joc.initializeaza(ecran)

    Joc.JMIN, tip_algoritm, incep, ADANCIME_MAX, mod_estimare = deseneaza_alegeri(ecran, tabla_curenta)
    ADANCIME_MAX = int(ADANCIME_MAX)
    if tip_algoritm == 'alphabeta':
        ADANCIME_MAX += 1 # daca se foloseste algoritmul alphabeta cresc adancimea cu 1
    Joc.JMAX = 'albe' if Joc.JMIN == 'negre' else 'negre'

    # initializare stare
    if incep == "eu":
        stare_curenta = Stare(tabla_curenta, Joc.JMIN, ADANCIME_MAX)
        print("\nEste randul jucatorului!\n")
    else:
        stare_curenta = Stare(tabla_curenta, Joc.JMAX, ADANCIME_MAX)
        print("\nEste randul calculatorului!\n")

    tabla_curenta.deseneaza_grid()

    while True:
        j_current = stare_curenta.j_curent
        if (j_current == Joc.JMIN):
            # muta jucatorul
            for event in pygame.event.get(): # pentru fiecare eveniment pe care l introduce user-ul
                if event.type == pygame.QUIT: # daca a iesit
                    afis_daca_final("force quit") # parametru pentru afisarea "early"
                    pygame.quit()  # inchide fereastra
                    sys.exit()
                elif event.type == pygame.MOUSEBUTTONDOWN: # daca a dat click
                    pos = pygame.mouse.get_pos()  # coordonatele clickului
                    for nod in Joc.coordonate_noduri: # pentru toate nodurile
                        if distEuclid(pos, nod) <= Joc.raza_pct: # daca a facut click pe un nod
                            if (j_current == 'albe'): # am pus piese in variabile mai usor de urmarit
                                piese_curente = stare_curenta.tabla_joc.piese_albe
                                piese_adverse = stare_curenta.tabla_joc.piese_negre
                            else:
                                piese_curente = stare_curenta.tabla_joc.piese_negre
                                piese_adverse = stare_curenta.tabla_joc.piese_albe
                            if nod not in piese_curente + piese_adverse: # daca a dat click pe un nod gol
                                if stare_curenta.tabla_joc.nod_piesa_selectata: # daca selectase un nod
                                    n0 = stare_curenta.tabla_joc.coordonate_noduri.index(nod) # nodul gol
                                    n1 = stare_curenta.tabla_joc.coordonate_noduri.index(stare_curenta.tabla_joc.nod_piesa_selectata) # nodul selectat
                                    piesa_capturata = capturare(nod, stare_curenta.tabla_joc.nod_piesa_selectata, piese_adverse) # daca a capturat o piesa cu aceasta mutare
                                    if piesa_capturata: # daca da
                                        piese_adverse.remove(piesa_capturata) # am sters piesa respectiva
                                        piese_curente.remove(stare_curenta.tabla_joc.nod_piesa_selectata)
                                        piese_curente.append(nod) # am mutat piesa selectata
                                        stare_curenta.tabla_joc.nod_piesa_selectata = False # am resetat selectarea de piese
                                        t_juc_dupa = int(round(time.time() * 1000)) # calcul pentru timpul petrecut de user la aceasta mutare
                                        mutari_juc += 1 # incrementarea mutarilor jucatorului
                                        print("Jucatorul a \"gandit\" timp de " + str(
                                            t_juc_dupa - t_juc_inainte) + " milisecunde.")
                                        afis_daca_final(stare_curenta) # daca am ajuns la final
                                        # (trebuie verificat si aici deoarece dupa o capturare tot jucatorul muta)
                                    elif ((n0, n1) in Joc.muchii or (n1, n0) in Joc.muchii): # daca nu a capturat
                                        l_puteam_captura = puteam_captura(stare_curenta, Joc.JMIN) # verific daca putea captura
                                        for piesa_pierduta in l_puteam_captura:
                                            # daca da, am eliminat fiecare piesa care putea captura
                                            lin = int(piesa_pierduta[1]/100)+1
                                            col = int(piesa_pierduta[0]/100)+1
                                            print("Puteai captura cu piesa de pe linia " + str(lin) + " coloana " + str(col) + ".")
                                            piese_curente.remove(piesa_pierduta)
                                        if stare_curenta.tabla_joc.nod_piesa_selectata not in l_puteam_captura:
                                            # daca piesa mutata nu a fost stearsa, o mut
                                            piese_curente.remove(stare_curenta.tabla_joc.nod_piesa_selectata)
                                            piese_curente.append(nod)
                                        stare_curenta.tabla_joc.nod_piesa_selectata = False # am resetat selectarea de piese
                                        stare_curenta.j_curent = Joc.jucator_opus(stare_curenta.j_curent) # am schimbat jucatorul
                                        t_juc_dupa = int(round(time.time() * 1000))
                                        mutari_juc += 1
                                        print("Jucatorul a \"gandit\" timp de " + str(
                                            t_juc_dupa - t_juc_inainte) + " milisecunde.")
                                        print("\nEste randul calculatorului!\n")
                            else:
                                if nod in piese_curente: # daca a dat click pe o piesa curenta
                                    if stare_curenta.tabla_joc.nod_piesa_selectata: # daca era deja selectata
                                        stare_curenta.tabla_joc.nod_piesa_selectata = False
                                    else: # daca nu, o selectez pe ea
                                        stare_curenta.tabla_joc.nod_piesa_selectata = nod
                            stare_curenta.tabla_joc.deseneaza_grid()

        # --------------------------------
        else:  # jucatorul e JMAX (calculatorul)
            # Mutare calculator

            # preiau timpul in milisecunde de dinainte de mutare
            t_inainte = int(round(time.time() * 1000))
            if tip_algoritm == 'minimax':
                stare_actualizata = min_max(stare_curenta, mod_estimare)
            else:
                stare_actualizata = alpha_beta(-500, 500, stare_curenta, mod_estimare)
            stare_curenta.tabla_joc = stare_actualizata.stare_aleasa.tabla_joc
            print("Tabla dupa mutarea calculatorului")
            print(str(stare_curenta))

            print("Estimare stare curenta: " + str(stare_curenta.estimare))

            stare_curenta.tabla_joc.deseneaza_grid()
            # preiau timpul in milisecunde de dupa mutare
            t_dupa = int(round(time.time() * 1000))
            t_calc = t_dupa - t_inainte
            print("Calculatorul a \"gandit\" timp de " + str(t_calc) + " milisecunde.")
            t_l.append(t_calc)

            print("Nr mutari generate: " + str(mutari_gen))
            n_l.append(mutari_gen)
            mutari_gen = 0

            if (afis_daca_final(stare_curenta)):
                break

            # daca nu s-a realizat o capturare, schimb jucatorul cu cel opus
            if not stare_curenta.tabla_joc.capturat:
                stare_curenta.j_curent = Joc.jucator_opus(stare_curenta.j_curent)
                print("\nEste randul jucatorului!\n")
            else:
                afis_daca_final(stare_curenta)
                time.sleep(1) # muta prea repede
            mutari_pc += 1
            t_juc_inainte = int(round(time.time() * 1000))



if __name__ == "__main__":
    main()
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()