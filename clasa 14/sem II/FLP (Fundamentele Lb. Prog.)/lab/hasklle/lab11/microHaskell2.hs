--3
import Data.List
import Data.Maybe

type Name = String

data  Value  =  VBool Bool
        |VInt Int
        |VFun (Value -> Value)
        |VError

data  Hask  = HTrue | HFalse
        |HIf Hask Hask Hask
        |HLit Int
        |Hask :==: Hask
        |Hask :+:  Hask
        |HVar Name
        |HLam Name Hask
        |Hask :$: Hask
        |Hask :*:  Hask
        |HLet Name Hask Hask
        deriving (Read, Show)


infix 4 :==:
infixl 6 :+:
infixl 7 :*:
infixl 9 :$:

type  HEnv  =  [(Name, Value)]


showV :: Value -> String
showV (VBool b)   =  show b
showV (VInt i)    =  show i
showV (VFun _)    =  "Can't show function"
showV (VError)    =  "Can't show error"

showV2 :: Maybe Value -> String
showV2 (Just x) = showV x
showV2 _ _ = "Nothing"


eqV :: Value -> Value -> Bool
eqV (VBool b) (VBool c)    =  b == c
eqV (VInt i) (VInt j)      =  i == j
eqV (VFun _) (VFun _)      =  error "Can't compare function"
eqV (VError ) (VError)     =  error "Can't compare errors"
eqV _ _               = False

eqV2 :: Maybe Value -> Maybe Value -> Bool
eqV2 (Just x) (Just y) = eqV x y
eqV2 _ _ = Nothing


hEval :: Hask -> HEnv -> Maybe Value
hEval HTrue r =  Just(VBool True)
hEval HFalse r =  Just(VBool False)

hEval (HIf c d e) r  = hif (hEval c r) (hEval d r) (hEval e r)
  where  hif (Just (VBool b)) (Just v) (Just w)  =  if b then (Just v) else (Just w)
         hif _ _ _ = Nothing

hEval (HLit x) r = Just (VInt x)
hEval (HVar s) r = Just (lookUp r s)
hEval (HLam x exp) r = Just (VFun (\v -> hEval exp ((x, v):r)))

hEval (e1 :==: e2) r = heq v1 v2
    where 
      v1 = Just (hEval e1 r) 
      v2 = Just (hEval e2 r) 
      heq (Just (VInt i)) (Just (VInt j)) = Just (VBool (i==j))
      heq _ _ = Nothing

hEval (x :+: y) r = hADD (hEval x r) (hEval y r)
    where
        hADD (Just (VInt a)) (Just (VInt b)) = Just (VInt (a + b))
        hADD _ _ = Nothing

hEval (x :*: y) r = hMUL (hEval x r) (hEval y r)
    where
        hMUL (Just (VInt a)) (Just (VInt b)) = Just (VInt (a * b))
        hMUL _ _ = Nothing

hEval (x :$: y) r = hLAM (hEval x r) (hEval y r)
    where
        hLAM (Just (VFun f)) (Just x) = Just (f x)
        hLAM _ _ = Nothing

hEval (HLet x ex e) r = hEval e ((x, (hEval ex r)):r)

lookUp :: HEnv -> Name -> Maybe Value
lookUp [] t = Nothing
lookUp ((s, v):xs) t
    | s == t = (Just v)
    | otherwise = lookUp xs t


--1
run :: Hask -> String
run pg = showV2 (hEval pg [("x", VInt 1), ("y", VInt 3)])


--2.1
example1 = (((HLam "x" (HLam "y" ((HVar "x") :+: (HVar "y")))) :$: (HLit 1)) :$: (HLit 2))
result1 = run example1

example2 = (HVar "x") :+: (HVar "y")
result2 = run example2

example3 = (HLit 1) :+: (HLit 4)
result3 = run example3

h0 =  (HLam "x" (HLam "y" ((HVar "x") :+: (HVar "y"))))
      :$: (HLit 3)
      :$: (HLit 4)

f = ( \ x -> if x == 1 then x + 2 else x + 10 ) $ (2 + 3)

test_h0 = eqV2 (hEval h0 []) (Just(VInt 7))

h1 = HLet "x" (HLit 3) ((HLit 4) :+: HVar "x")
