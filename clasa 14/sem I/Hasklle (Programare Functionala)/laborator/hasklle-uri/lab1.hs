myInt = 23

double :: Integer -> Integer
double x = 2*x

triple :: Integer -> Integer
triple x = 3*x

modul :: Integer -> Integer
modul x
        | x >= 0  = x
        | x < 0 = -x
        | otherwise = 0

maxim x y =
    if (x > y)
        then x
    else y

maxim3 x y z = let u = (maxim x y) in (maxim u z)

maxim4 x y z t =
     let
          a = maxim3 x y z
     in
          maxim a t

sumapatrate :: Integer -> Integer -> Integer 
sumapatrate x y = x*x + y*y

paritate x
        | even x = "par"
        | otherwise = "impar"

factorial x
        | x == 0 = 1
        | x >= 1 = x * factorial (x-1)

chestie x y
        | x > y*2 = "primul"
        | otherwise = "al doilea"