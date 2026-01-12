--1
firstEl :: [(a, b)] -> [a]
firstEl = map fst


--2
sumList :: [[Int]] -> [Int]
sumList = map sum


--3
prel2 :: [Int] -> [Int]
prel2 = map (\x -> if(x `mod` 2 == 0) then x `div` 2 else x*2)


--4
charInList :: Char -> [String] -> [String]
charInList c list= filter (elem c) list


--5
patrateImpare :: [Int] -> [Int]
patrateImpare list = map (^2) (filter odd list)


--6
patratePozImpare :: [Int] -> [Int]
patratePozImpare list = map (^2) ( map fst ( filter (odd.snd) (zip list [1..]) ) )


--7
numaiVocale :: [String] -> [String]
numaiVocale = map (filter(`elem` "aeiouAEIOU"))


--8
myMap :: (a -> b) -> [a] -> [b]
myMap fct [] = []
myMap fct (x : list) = fct x : myMap fct list

myFilter :: (a -> Bool) -> [a] -> [a]
myFitler cond [] = []
myFilter cond (x : list)
    |cond x = x : myFilter cond list
    |otherwise = myFilter cond list


--9
sumPatrateImpare :: [Int] -> Int
sumPatrateImpare list = sum (map (^2) (filter odd list))


--10
allTrue :: [Bool] -> Bool
allTrue = foldr (&&) True


--11.a
rmChar :: Char -> String -> String
rmChar c list = filter (/= c) list

--11.b
rmCharsRec :: String -> String -> String
rmCharsRec [] cuv = cuv
rmCharsRec (x : elim) cuv = rmCharsRec elim (rmChar x cuv)

--11.c
rmCharsFold :: String -> String -> String
rmCharsFold elim cuv = foldr rmChar cuv elim
