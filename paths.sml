datatype 'a tree = Empty | Tree of 'a tree * 'a * 'a tree
datatype 'a step = Push of 'a tree | Shift of 'a | Test of 'a

fun restore (xs, nil) = xs
  | restore (xs, Shift x :: ss) = restore (x :: xs, ss)
  | restore (xs, _ :: ss) = restore (xs, ss)

fun push (Empty, ss) = ss
  | push (Tree (Empty, x, Empty), ss) = Test x :: ss
  | push (Tree (a, x, b), ss) = Shift (~x) :: Push b :: Push a :: Shift x :: ss

fun visit (_, ps, nil) = ps
  | visit (c, ps, Push xs :: ss) = visit (c, ps, push (xs, ss))
  | visit (c, ps, Shift x :: ss) = visit (c + x, ps, ss)
  | visit (c, ps, Test x :: ss) = 
    if x = c then
      visit (c, restore (x :: nil, ss) :: ps, ss)
    else
      visit (c, ps, ss)

datatype 'a step = Zero | One of 'a | Many of 'a

fun many (c, x, ss) = if x < c then Many (2*x) :: Many (2*x+1) :: One x :: ss else Zero :: ss

fun make (c, b :: a :: us, One x :: vs) = make (c, Tree (a, x mod 2, b) :: us, vs)
  | make (c, us, Zero :: vs) = make (c, Empty :: us, vs)
  | make (c, us, Many x :: vs) = make (c, us, many (c, x, vs))
  | make (_, xs :: _, _) = xs
  | make _ = Empty

val tree = make (64, nil, Many 1 :: nil)
val paths = visit (4, nil, Push tree :: nil)
