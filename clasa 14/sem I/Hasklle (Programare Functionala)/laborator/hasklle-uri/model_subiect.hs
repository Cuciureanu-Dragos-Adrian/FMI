--I. Grile

--1
--a

--2
--c

--3
--a

--4
--a

--5
--a

--6
--a

--7
--a

--8
--a

--9
--a

--10
--a


--II. Liste

--1
fct1 :: String -> String -> String
fct1 _ [] = []
fct1 [] _ = []
fct1 (x : list1) (y : list2)
    | x == y = x : fct1 list1 list2
    | otherwise = []

--2
fct2 :: [Int] -> [Int] -> Int
fct2 _ [] = 0
fct2 [] _ = 0
fct2 (x : list1) (y : list2) = if length (x : list1) == length (y : list2) 
                                then x^2 * y^2 + fct2 list1 list2 
                                else error "listele au lungimi diferite"


--III. Tipuri de date
data PairInt = P Int Int
    deriving Show
data MyList = L [PairInt]
    deriving Show
data Exp = I Int | Add Exp Exp | Mul Exp Exp
    deriving (Eq, Show)

class MyClass m where
    toExp :: m -> Exp

--a
instance MyClass MyList where
    toExp (L [])  = I 1
    toExp (L (x : list)) = Mul a b
        where
            P m n = x
            a = Add (I m) (I n)
            b = toExp (L list)

--b
eval :: MyList -> Int
eval list = eval' (toExp list) where
    eval' (I x) = x
    eval' (Add exp1 exp2) = eval' exp1 + eval' exp2
    eval' (Mul exp1 exp2) = eval' exp1 * eval' exp2
