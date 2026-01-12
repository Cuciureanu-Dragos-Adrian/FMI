import Data.List 
import Data.Maybe


type Nume = String
data Prop
    = Var Nume
    | F
    | T
    | Not Prop
    | Prop :|: Prop
    | Prop :&: Prop
    | Prop :->: Prop
    | Prop :<->: Prop
    deriving Eq
infixr 2 :|:
infixr 3 :&:


--1
p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

p3 :: Prop
p3 = (Var "P" :&: (Var"Q" :|: Var "R")) :&: ((Not (Var "P") :&: Not (Var "Q")) :&: (Not (Var "P") :&: Not (Var "R")))


--2
instance Show Prop where
    show (Var p) = p 
    show F = "F"
    show T = "T"
    show (Not p) = "(~" ++ show p ++ ")"
    show (p :|: q) = "(" ++ show p ++ "|" ++ show q ++ ")"
    show (p :&: q) = "(" ++ show p ++ "&" ++ show q ++ ")"
    show (p :->: q) = "(" ++ show p ++ "->" ++ show q ++ ")"
    show (p :<->: q) = "(" ++ show p ++ "<->" ++ show q ++ ")"

 
test_ShowProp :: Bool
test_ShowProp =
    show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a


--3
eval :: Prop -> Env -> Bool
eval (Var p) e = impureLookup p e
eval F e = False
eval T e = True
eval (Not p) e = not (eval p e)
eval (p :|: q) e = (eval p e) || (eval q e)
eval (p :&: q) e = (eval p e) && (eval q e)
eval (p :->: q) e = not(eval p e) || (eval q e)
eval (p :<->: q) e = (not(eval p e) || (eval q e)) && ((eval p e) || not(eval q e))

test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)]


--4
variabile :: Prop -> [Nume]
variabile T = []
variabile F = [] 
variabile (Var x) = [x]
variabile (Not p) = variabile p
variabile (p :|: q) = nub(variabile p ++ variabile q)
variabile(p :&: q) = nub(variabile p ++ variabile q)
variabile(p :->: q) = nub(variabile p ++ variabile q)
variabile(p :<->: q) = nub(variabile p ++ variabile q)
 
test_variabile =
  variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]


--5
envs :: [Nume] -> [Env]
envs nume =
    let submultimi = subsequences nume
    in map produsEnv submultimi
  where
    produsEnv submultime = map(valuation submultime) nume

    valuation :: [Nume] -> Nume -> (Nume, Bool)
    valuation subm n
      | n `elem` subm = (n, True)
      | otherwise = (n, False)
 
test_envs = 
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]


--6
satisfiabila :: Prop -> Bool
satisfiabila x = any (==True) (map (eval x) (envs (variabile x)))
 
test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q")
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P")


--7
valida :: Prop -> Bool
valida x = not (satisfiabila (Not x))

test_valida1 = valida (Not (Var "P") :&: Var "Q")
test_valida2 = valida (Not (Var "P") :|: Var "P")


--9
--am modificat exercitiile anterioare


--10
echivalenta :: Prop -> Prop -> Bool
echivalenta x y = all (\env -> eval (x :<->: y) env) (envs (nub (variabile x ++ variabile y)))
 
test_echivalenta1 =
  (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P")) :|: Not (Var "Q"))
test_echivalenta2 = Var "P" `echivalenta` Var "Q"
test_echivalenta3 = (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))