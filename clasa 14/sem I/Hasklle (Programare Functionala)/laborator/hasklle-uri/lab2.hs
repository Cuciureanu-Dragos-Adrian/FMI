--1
poly2 :: Double -> Double -> Double -> Double -> Double
poly2 a b c x = a*x^2+b*x+c


--2
eeny :: Integer -> String
eeny x
    | even x = "eeny"
    | otherwise = "meeny"


--3.1
fizzbuzz :: Integer -> String
fizzbuzz x
    | x `mod` 15 == 0 = "FizzBuzz"
    | x `mod` 3 == 0 = "Fizz"
    | x `mod` 5 == 0 = "Buzz"
    | otherwise = ""

--3.2
fizzbuzz2 :: Integer -> String
fizzbuzz2 x = 
    if(x `mod` 15 == 0)
        then "FizzBuzz"
    else if(x `mod` 3 == 0)
        then "Fizz"
    else if(x `mod` 5 == 0)
        then "Buzz"
    else ""


--4.1
tribonacci :: Integer -> Integer
tribonacci n
    | n == 1 = 1
    | n == 2 = 1
    | n == 3 = 2
    | otherwise = tribonacci (n-1) + tribonacci (n-2) + tribonacci (n-3)

--4.2
tribonacci2 :: Integer -> Integer
tribonacci2 1 = 1
tribonacci2 2 = 1
tribonacci2 3 = 2
tribonacci2 n = tribonacci2 (n-1) + tribonacci2 (n-2) + tribonacci2 (n-3)


--5
binomial :: Integer -> Integer -> Integer
binomial n k
    | k == 0 = 1
    | n == 0 = 0
    | otherwise = binomial (n-1) k + binomial (n-1) (k-1)


--6.a
verifL :: [Int] -> Bool
verifL lista
    | even (length lista) = True
    | otherwise = False

--6.b
takefinal :: [Int] -> Int -> [Int]
takefinal lista n
    | length lista < n = lista
    | otherwise = drop (l - n) lista 
    where l = length lista

takefinal2 :: [a] -> Int -> [a]
takefinal2 lista n
    | length lista < n = lista
    | otherwise = drop (l - n) lista 
    where l = length lista

--6.c
remove :: [a] -> Int -> [a]
remove lista n
    | length lista < n = lista
    | otherwise = take (n-1) lista ++ drop (l - n + 1) lista 
    where l = length lista


--7.a
myreplicate :: Int -> Int -> [Int]
myreplicate n v
    | n == 0 = []
    | otherwise = v:lista 
    where lista = myreplicate (n-1) v

--7.b
sumImp :: [Int] -> Int
sumImp lista
    | lista == [] = 0
    | odd (head lista) = head lista + sumImp (tail lista) 
    | otherwise = sumImp (tail lista) 

--7.c
totalLen :: [String] -> Int
totalLen lista
    | lista == [] = 0
    | head lista /= "" && head (head lista) == 'A' = length (head lista) + totalLen (tail lista) 
    | otherwise = totalLen (tail lista) 