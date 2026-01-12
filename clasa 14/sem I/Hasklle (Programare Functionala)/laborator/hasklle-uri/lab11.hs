import Data.Maybe
import Data.List

type Name = String

data  Value  =  VBool Bool
     |VInt Int
     |VFun (Value -> Value)
     |VError

data  Hask = HTrue | HFalse
     |HIf Hask Hask Hask
     |HLit Int
     |Hask :==: Hask
     |Hask :+:  Hask
     |HVar Name
     |HLam Name Hask
     |Hask :$: Hask
     |Hask :*:  Hask

infix 4 :==:
infixl 6 :+:
infixl 7 :*:
infixl 9 :$:

type  HEnv  =  [(Name, Value)]

--1
instance Show Value where
     show (VInt x) = show x
     show (VBool k) = show k
     show (VFun fct) = show "can't show function"
     show (VError) = show "can't show error" 


--2
instance Eq Value where
     VInt x == VInt y = x == y
     VBool k == VBool l = k == l
     VFun fct1 == VFun fct2 = error "can't compare functions"
     VError == VError = error "can't compare errors"
     _ == _ = error "can't compare different types"


--3
hEval :: Hask -> HEnv -> Value
hEval HTrue r =  VBool True
hEval HFalse r =  VBool False
hEval (HIf c d e) r  = hif (hEval c r) (hEval d r) (hEval e r)
  where  hif (VBool b) v w  =  if b then v else w
         hif _ _ _ = VError
hEval (HLit x) r = VInt x
--hEval (x :==: y) r 
--    | (hEval x r) == (hEval y r) = VBool ((hEval x r) == (hEval y r))
--    | otherwise = error "can't equalize"
--hEval ((HLit x) :+: (HLit y)) r = VInt (x + y)

-- (((HLit x) :+: (HLit y)) :+: HVar "x") :*: (HLit 6)
--hEval (_ :+: _) r = error "can add only 2 literals"

hEval (e1 :==: e2) r = heq v1 v2
    where 
      v1 = hEval e1 r 
      v2 = hEval e2 r 
      heq (VInt i) (VInt j) = VBool (i==j)
      heq _ _ = error "can't equalize"

hEval (e1 :+: e2) r = add v1 v2
    where 
      v1 = hEval e1 r 
      v2 = hEval e2 r 
      add (VInt i) (VInt j) = VInt (i + j)
      add _ _ = error "can add only 2 literals"

hEval (HVar v) r = if ((lookup v r) == Nothing) 
                    then error "variable was not found"
                    else fromJust (lookup v r)
hEval (HLam x fct) r = VFun (\v -> hEval fct ( (x, v) : r ))
hEval (lfct :$: param) r = lam (hEval lfct r) (hEval param r)
    where lam (VFun fct) x = fct x
          lam _ _ = error "first parameter is not a function"

hEval (e1 :*: e2) r = add v1 v2
    where 
      v1 = hEval e1 r 
      v2 = hEval e2 r 
      add (VInt i) (VInt j) = VInt (i * j)
      add _ _ = error "can multiply only 2 literals"


--4
run :: Hask -> String
run pg = show (hEval pg [("x", VInt 1), ("y", VInt 3)])

example1 = (((HLam "x" (HLam "y" ((HVar "x") :+: (HVar "y")))) :$: (HLit 1)) :$: (HLit 2))
result1 = run example1

example2 = (HVar "x") :+: (HVar "y")
result2 = run example2

example3 = (HLit 1) :+: (HLit 4)
result3 = run example3
