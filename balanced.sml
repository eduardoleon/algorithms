datatype tree = Empty | Tree of tree * tree
datatype step = One | Many of tree

fun visit (m :: n :: ns, One :: ss) =
    let
      val p = Int.min (m, n)
      val q = Int.max (m, n)
    in
      if q - p > 1 then false else visit (q + 1 :: ns, ss)
    end
  | visit (ns, Many Empty :: ss) = visit (0 :: ns, ss)
  | visit (ns, Many (Tree (a, b)) :: ss) = visit (ns, Many a :: Many b :: One :: ss)
  | visit _ = true

fun balanced xs = visit (nil, Many xs :: nil)

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
