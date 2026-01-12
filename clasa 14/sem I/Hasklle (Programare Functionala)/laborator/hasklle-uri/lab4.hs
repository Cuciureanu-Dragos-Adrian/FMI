--1
factori :: Int -> [Int]
factori x = [divizor | divizor <- [1..x], x `mod` divizor == 0]


--2
prim :: Int -> Bool
prim n = (length (factori n) == 2)


--3
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], length (factori x) == 2]


--4
myzip3 :: [a] -> [b] -> [c] -> [(a, b, c)]
myzip3 [] _ _ = []
myzip3 _ [] _ = []
myzip3 _ _ [] = []
myzip3 (x:list1) (y:list2) (z:list3) = (x, y, z) : myzip3 list1 list2 list3

myzip32 :: [a] -> [b] -> [c] -> [(a, b, c)]
myzip32 list1 list2 list3 = [(x, y, z) | ((x, y), z) <- zip (zip list1 list2) list3]


--5
ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (x:xs) = and [a < b | (a, b) <- zip (x:xs) xs]


--6
ordonataNat1 :: [Int] -> Bool
ordonataNat1 [] = True
ordonataNat1 [x] = True
ordonataNat1 (x:y:xs)
    | x < y = ordonataNat1 (y:xs)
    | otherwise = False


--7
ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata [] semn = True
ordonata [x] semn = True
ordonata (x:xs) semn = and [semn a b | (a, b) <- zip (x:xs) xs]


--8
infixr 6 *<*  
(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool
(x, y) *<* (z, t)
    | (x + y) > (z + t) = True
    | otherwise = False


--9
compuneList :: (b -> c) -> [(a -> b)] -> [( a -> c)]
compuneList f listf = [f.g | g <- listf]


--10
aplicaList :: a -> [(a -> b)] -> [b]
aplicaList x listf = [semn x | semn <- listf]

