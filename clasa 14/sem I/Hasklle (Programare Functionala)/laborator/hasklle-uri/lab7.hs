--1
data Fruct
     = Mar String Bool
     | Portocala String Int

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10

listaFructe = [Mar "Ionatan" False,
  Portocala "Sanguinello" 10,
  Portocala "Valencia" 22,
  Mar "Golden Delicious" True,
  Portocala "Sanguinello" 15,
  Portocala "Moro" 12,
  Portocala "Tarocco" 3,
  Portocala "Moro" 12,
  Portocala "Valencia" 2,
  Mar "Golden Delicious" False,
  Mar "Golden" False,
  Mar "Golden" True]

soiuriS = ["Tarocco", "Moro" , "Sanguinello"]



--1.1
ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia x = case x of 
   Portocala s i -> elem s soiuriS 
   Mar _ _ -> False 

ePortocala (Portocala s i) = True 
ePortocala (Mar _ _ ) = False 

ePortocalaDeSicilia2 :: Fruct -> Bool
ePortocalaDeSicilia2 (Portocala s _ ) = elem s soiuriS 
ePortocalaDeSicilia2 (Mar _ _ ) = False 



--1.2
nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia [] = 0 
nrFeliiSicilia (Portocala s i : lfructe)  = if elem s soiuriS then i + nrFeliiSicilia lfructe else nrFeliiSicilia lfructe
nrFeliiSicilia (Mar _ _ : lfructe) = nrFeliiSicilia lfructe 

nrFeliiSicilia1 :: [Fruct] -> Int 
nrFeliiSicilia1 lista = sum [ i | Portocala s i <- lista, elem s soiuriS]

nrFeliiSicilia2 lista = foldr (+) 0 ( map (\ (Portocala s i ) -> i ) (filter ePortocalaDeSicilia lista ) )



--1.3
nrMereViermi :: [Fruct] -> Int
nrMereViermi lista = sum [ 1 | Mar _ True <- lista]



--2
type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa

pisica1 = Pisica "miau"
caine1 = Caine "ruf" "auf"


--2.1
vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow"
vorbeste (Caine _ _) = "Woof"



--2.2
rasa :: Animal -> Maybe String
rasa (Caine _ rasa) = Just rasa
rasa (Pisica _) = Nothing



--3
data Linie = L [Int]
data Matrice = M [Linie]



--3.1
verifica :: Matrice -> Int -> Bool
verifica (M linii) n = foldr (\(L line) buffer -> buffer && (sum line == n)) True linii

verifica2 :: Matrice -> Int -> Bool
verifica2 (M linii) n = and [sum line == n | L line <- linii]

test_verif1 = verifica (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 10
test_verif2 = verifica (M[L[2,20,3], L[4,21], L[2,3,6,8,6], L[8,5,3,9]]) 25



--3.2
doarPozN :: Matrice -> Int -> Bool
doarPozN (M linii) n = and [elem > 0 | L line <- linii, elem <- line, length(line) == n]

testPoz1 = doarPozN (M [L[1,2,3], L[-4,5], L[2,3,6,8], L[8,5,3]]) 3
testPoz2 = doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3



--3.3
corect :: Matrice -> Bool
corect (M linii) = let
    L primaLinie = head linii
    lungime = length(primaLinie)
    raspuns = and [length(line) == lungime | L line <- linii]
    in raspuns

testcorect1 = corect (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]])
testcorect2 = corect (M[L[1,2,3], L[4,5,8], L[3,6,8], L[8,5,3]])