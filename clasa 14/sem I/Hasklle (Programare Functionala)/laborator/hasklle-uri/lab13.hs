import Data.Monoid

data BinaryTree a =
  Leaf a
  | Node ( BinaryTree a ) ( BinaryTree a )
    deriving (Show, Eq)

foldTree :: ( a -> b -> b ) -> b -> BinaryTree a -> b
foldTree f i ( Leaf x ) = f x i
foldTree f i (Node l r ) = foldTree f ( foldTree f i r ) l

myTree = Node (Node ( Leaf 1) ( Leaf 2) ) (Node ( Leaf 3) (Leaf 4) )


instance Foldable BinaryTree where
  foldr = foldTree

-- foldMap :: Monoid m => (a -> m) -> t a -> m
-- foldr :: (a -> b -> b ) -> b -> t a -> b


--1

--1.1
celem :: (Eq a) => a -> [a] -> Bool
celem x xs = foldr (\y acc -> acc ||  x == y ) False xs

elemFoldMap :: (Foldable t, Eq a) => a -> t a -> Bool
elemFoldMap x xs = getAny $ foldMap  (\y -> Any (y==x) ) xs

elem :: (Foldable t, Eq a) => a -> t a -> Bool
elem x collection =
    getAny
    $ foldMap isAnyEqual collection
  where
    isAnyEqual y = Any (x == y)


--1.2
null1 :: (Foldable t) => t a -> Bool
null1 collection = foldr (\_ _ -> False) True collection

null2 :: (Foldable t) => t a -> Bool
-- null xs = foldr (\x acc -> acc && False) True xs
null2 xs = getAll (foldMap (\x -> All False) xs)


--1.3
lengthfoldMap :: (Foldable t) => t a -> Int
lengthfoldMap = getSum . foldMap (Sum . const 1)

lengthFoldr :: Foldable t => t a -> Int
lengthFoldr = foldr (\x acc -> acc + 1) 0

lengthFoldMap :: Foldable t => t a -> Int
lengthFoldMap xs = getSum (foldMap (\x -> Sum 1) xs)


--1.4
toListFoldr :: (Foldable t) => t a -> [a]
toListFoldr = foldr (:) []

toListFoldMap :: (Foldable t) => t a -> [a]
toListFoldMap = foldMap (\x -> [x])


--1.5
fold :: (Foldable t, Monoid m) => t m -> m
fold = foldMap id




--2

--2.1
data Constant a b = Constant b

instance Foldable (Constant a) where
    foldMap f (Constant x) = f x


--2.2
data Two a b = Two a b

instance Foldable (Two a) where
    foldMap f (Two x y) = f y


--2.3
data Three a b c = Three a b c

instance Foldable (Three a b) where
    foldMap f (Three x y z) = f z


--2.4
data Three' a b = Three' a b b

instance Foldable (Three' a) where
    foldMap f (Three' x y z) = f y <> f z


--2.4
data Four' a b = Four' a b b b

instance Foldable (Four' a) where
    foldMap f (Four' x y z t) = f y <> f z <> f t


--2.5
data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
    deriving Show
instance Foldable (GoatLord) where
    foldMap _ (NoGoat) = mempty
    foldMap f (OneGoat a) = f a
    foldMap f (MoreGoats x y z) = (foldMap f x) <> (foldMap f y) <> (foldMap f z)

goatlord1 = NoGoat
goatlord2 = OneGoat 5
goatlord3 = MoreGoats (OneGoat 5) NoGoat (MoreGoats (OneGoat 1) (OneGoat 6) NoGoat)