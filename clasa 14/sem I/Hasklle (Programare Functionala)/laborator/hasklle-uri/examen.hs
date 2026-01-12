import Prelude

--6
verif :: Ord t => [t] -> t -> Bool
verif [] n = True
verif (x : list) n 
  | x > n = verif list n
  | otherwise = False

f1 :: Ord t => [[t]] -> t -> Bool
f1 [] n = True 
f1 (list : lists) n
  | verif list n == True && (mod (length list) 2) == 1 = False
  | otherwise = f1 lists n

test1 = f1 [[1,2,3],[11,6,8,8],[2,3,4,5,6,7,8],[6,6,7,8,8,9]] 4
test2 = f1 [] 3
test3 = f1 [[1,2,3],[11,6,8,8],[2,3,4,5,6,7,8],[5,6,6,7,8,8,9]] 4
test4 = f1 [[1,2,3],[11,6,8,8],[2,3,4,5,6,7,8],[6,6,4,7,8,8,9]] 4


--2
verifPrefix :: Eq a => [a] -> [a] -> Bool
verifPrefix [] _ = True 
verifPrefix (x : prefix) (y : word) 
  | x == y = verifPrefix prefix word
  | otherwise = False

f2 :: Eq a => [a] -> [[a]] -> Bool
f2 prefix [] = True 
f2 prefix (word : words)
  | verifPrefix prefix word == True && (mod (length word) 2 == 0) = False 
  | otherwise = f2 prefix words

test5 = f2 "ana" ["ana are","mere","pere", "ana nu are nuci"]
test6 = f2 "ana" ["ana are","mere","pere", "ana are nuci"]
test7 = f2 "ana" ["mere", "pere"]
test8 = f2 "ana" []

expr = fmap (++ "lol") ["Hi,", "Hello"]


--3
data Identity a = Identity a
instance Foldable Identity where
  foldr f z (Identity x) = f x z

--4
data MyPair a b = P a b 
  deriving Show
data MyList a = L [a] 
  deriving  Show


class MyZip lp where
  zipL :: lp a -> lp b -> lp (MyPair  a b)
  unzipL ::  lp (MyPair  a b) -> MyPair (lp a) (lp b)

fromList :: MyList a -> [a]
fromList (L xs) = xs

aux1 :: [MyPair a b] -> [a]
aux1 [] = []
aux1 (P x y : list) = x : aux1 list

aux2 :: [MyPair a1 a2] -> [a2]
aux2 [] = []
aux2 (P x y : list) = y : aux2 list



instance MyZip MyList where
  zipL (L []) (L _) = L []
  zipL (L _) (L []) = L []
  zipL (L (x : list1)) (L (y : list2)) = L ((P x y) : fromList(zipL (L list1) (L list2)))
  unzipL (L []) = P (L []) (L [])
  unzipL (L ((P x y) : list)) = P (L (x : aux1 list)) (L (y : aux2 list))

test9 = zipL (L [1,2,3,4,5]) (L [4,5,6,7,8])
test10 = unzipL (L [P 1 4,P 2 5,P 3 6,P 4 7,P 5 8])