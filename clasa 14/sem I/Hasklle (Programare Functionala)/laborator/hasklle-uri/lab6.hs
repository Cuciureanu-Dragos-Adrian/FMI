import Data.List
import Data.Char
import GHC.Unicode

--1
rotate :: Int -> [Char] -> [Char]
rotate n list
    | n > length list || n < 0 = error "wrong input"
    | otherwise = (drop n list) ++ (take n list)


--3
makeKey :: Int -> [(Char, Char)]
makeKey n = zip ['A' .. 'Z'] (rotate n ['A' .. 'Z'])


--4
lookUp :: Char -> [(Char, Char)] -> Char
lookUp char tuple
    | length ( filter(\(x, y) -> x == char) tuple) > 0 = snd (head (filter(\(x, y) -> x == char) tuple))
    | otherwise = char


--5
encipher :: Int -> Char -> Char
encipher n char 
    | x >= 'A' && x <= 'Z' && char >= 'A' && char <= 'Z' = x
    | x >= 'a' && x <= 'z' && char >= 'a' && char <= 'z' = x
    | otherwise = toEnum( fromEnum x -26) 
    where x = toEnum (fromEnum char + (mod n 26) ) :: Char


--6
normalize :: String -> String
normalize list = map toUpper (filter isAlphaNum list)


--7
encipherStr :: Int -> String -> String
encipherStr n list = map (encipher n) (normalize list)


--8
swap :: (a, b) -> (b, a)
swap (x, y) = (y, x)

reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey = map swap


--9
decipher :: Int -> Char -> Char
decipher n = encipher (26 - (mod n 26))

decipherStr :: Int -> String -> String
decipherStr n list = map (\x -> if elem x ['A' .. 'Z'] then decipher n x else x) (filter (`elem` ' ' : ['A' .. 'Z'] ++ ['0' .. '9']) list)