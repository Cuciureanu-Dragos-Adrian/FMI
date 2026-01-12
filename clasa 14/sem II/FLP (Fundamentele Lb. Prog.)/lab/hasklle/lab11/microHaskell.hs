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
showV (VFun _)    =  "<function>"
showV (VError)    =  "<error>"


eqV :: Value -> Value -> Bool
eqV (VBool b) (VBool c)    =  b == c
eqV (VInt i) (VInt j)      =  i == j
eqV (VFun _) (VFun _)      =  error "Unknown"
eqV (VError ) (VError)      =  error "Unknown"
eqV _ _               = False


hEval :: Hask -> HEnv -> Value
hEval HTrue r =  VBool True
hEval HFalse r =  VBool False

hEval (HIf c d e) r  = hif (hEval c r) (hEval d r) (hEval e r)
  where  hif (VBool b) v w  =  if b then v else w
         hif _ _ _ = error "Can't evaluate IF values!"

hEval (HLit x) r = VInt x
hEval (HVar s) r = lookUp r s
hEval (HLam x exp) r = VFun (\v -> hEval exp ((x, v):r))

hEval (e1 :==: e2) r = heq v1 v2
    where 
      v1 = hEval e1 r 
      v2 = hEval e2 r 
      heq (VInt i) (VInt j) = VBool (i==j)
      heq _ _ = error "Can't equalize values"

hEval (x :+: y) r = hADD (hEval x r) (hEval y r)
    where
        hADD (VInt a) (VInt b) = VInt (a + b)
        hADD _ _ = error "Can't add different Data Types!"

hEval (x :*: y) r = hMUL (hEval x r) (hEval y r)
    where
        hMUL (VInt a) (VInt b) = VInt (a * b)
        hMUL _ _ = error "Can't multiply different Data Types!"

hEval (x :$: y) r = hLAM (hEval x r) (hEval y r)
    where
        hLAM (VFun f) x = f x
        hLAM _ _ = error "Invalid lambda argument Types!"

hEval (HLet x ex e) r = hEval e ((x, (hEval ex r)):r)

lookUp :: HEnv -> Name -> Value
lookUp [] t = error "Value not found!"
lookUp ((s, v):xs) t
    | s == t = v
    | otherwise = lookUp xs t


--1
run :: Hask -> String
run pg = showV (hEval pg [("x", VInt 1), ("y", VInt 3)])


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

test_h0 = eqV (hEval h0 []) (VInt 7)

h1 = HLet "x" (HLit 3) ((HLit 4) :+: HVar "x")

# (NOT(ISNULL({!$Record.SVC_WebCommerceCustomerId__pc})) && (ISCHANGED({!$Record.VIPstatus__c}) || ISCHANGED({!$Record.PersonHasOptedOutOfEmail}) ||  ISCHANGED({!$Record.SVC_WebCommerceCustomerId__pc})) ) || (ISNEW() && NOT(ISNULL({!$Record.SVC_WebCommerceCustomerId__pc})))