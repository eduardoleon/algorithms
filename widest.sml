datatype tree = Empty | Tree of tree * tree

fun inner (c, ms, nil) = (c, ms)
  | inner (c, ms, Empty :: ns) = inner (c, ms, ns)
  | inner (c, ms, Tree (a, b) :: ns) = inner (c + 1, a :: b :: ms, ns)

fun outer (b, nil) = b
  | outer (b, ns) =
    let val (c, ms) = inner (0, nil, ns)
    in outer (Int.max (b, c), ms) end

fun widest1 n = outer (0, n :: nil)

fun inner (c, ms, nil) = (c, ms)
  | inner (c, ms, Empty :: ns) = inner (c, ms, ns)
  | inner (c, ms, Tree (a, b) :: ns) = inner (c + 1, b :: ms, a :: ns)

fun outer (b, nil) = b
  | outer (b, ns) =
    let val (c, ms) = inner (0, nil, ns)
    in outer (Int.max (b, c), ms) end

fun widest2 n = outer (0, n :: nil)

datatype step = Zero | One | Many of int

fun many (c, x, ss) = if x < c then Many (2*x) :: Many (2*x+1) :: One :: ss else Zero :: ss

fun make (c, b :: a :: us, One :: vs) = make (c, Tree (a, b) :: us, vs)
  | make (c, us, Zero :: vs) = make (c, Empty :: us, vs)
  | make (c, us, Many x :: vs) = make (c, us, many (c, x, vs))
  | make (_, xs :: _, _) = xs
  | make _ = Empty

val small = make (16, nil, Many 1 :: nil)
val large = make (64, nil, Many 1 :: nil)
val unbal = Tree (small, large)
