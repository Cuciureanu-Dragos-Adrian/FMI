import Data.Char

--1
nrV :: String -> Int
nrV lista
    | null lista = 0
    | (head lista) `elem` vocale = 1 + nrV (tail lista)
    | otherwise = nrV (tail lista)
    where vocale = "aeiouAEIOU"

nrVocale :: [String] -> Int
nrVocale lista
    | null lista = 0
    | (head lista) == reverse(head lista) = nrV (head lista) + nrVocale (tail lista)
    | otherwise = nrVocale(tail lista)


--2
adaugaElem :: Int -> [Int] -> [Int]
adaugaElem elem lista
    | null lista = []
    | even (head lista) = (head lista) : elem : adaugaElem elem (tail lista)
    | otherwise = (head lista) : adaugaElem elem (tail lista)


--3
divizori :: Int -> [Int]
divizori elem = [x | x <- [1 .. elem], elem `mod` x == 0]


--4
listaDiv :: [Int] -> [[Int]]
listaDiv lista 
    | null lista = []
    | otherwise = divizori (head lista) : listaDiv(tail lista)


--5.a
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec a b lista
    | null lista = []
    | (head lista) >= a && (head lista) <= b = (head lista) : inIntervalRec a b (tail lista)
    | otherwise = inIntervalRec a b (tail lista)

--5.b
inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp a b lista = [x | x <- lista, x >= a, x <= b]


--6.a
pozitiveRec :: [Int] -> Int
pozitiveRec lista
    | null lista = 0
    | (head lista) > 0 = 1 + pozitiveRec (tail lista)
    | otherwise = pozitiveRec (tail lista)

--6.b
pozitiveComp :: [Int] -> Int
pozitiveComp lista = length [x | x <- lista, x > 0]


--7.a
pozImpare :: Int -> [Int] -> [Int]
pozImpare poz lista
    | null lista = []
    | odd (head lista) = poz : pozImpare (poz + 1) (tail lista)
    | otherwise = pozImpare (poz + 1) (tail lista)

pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec lista = pozImpare 0 lista

--7.b
pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp lista = [ y | (x,y) <- zip lista [0 ..], odd x ]


--8.a
multDigitsRec :: [Char] -> Int
multDigitsRec lista
    | null lista = 1
    | isDigit (head lista) = digitToInt (head lista) * multDigitsRec (tail lista)
    | otherwise = multDigitsRec (tail lista)

--8.b
multDigitsComp :: [Char] -> Int
multDigitsComp lista = product [ digitToInt (x) | x <- lista, isDigit (x)]