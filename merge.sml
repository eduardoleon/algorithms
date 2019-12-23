datatype 'a tree = Empty | Tree of 'a tree * 'a * 'a tree
datatype 'a step = One of 'a | Many of 'a tree

fun step nil = NONE
  | step (One x :: ss) = SOME (x, ss)
  | step (Many Empty :: ss) = step ss
  | step (Many (Tree (a,x,b)) :: ss) = step (Many b :: One x :: Many a :: ss)

fun one (xs, NONE) = xs
  | one (xs, SOME (x, ys)) = one (x :: xs, step ys)

fun two (xs, ys, NONE) = one (xs, ys)
  | two (xs, NONE, zs) = one (xs, zs)
  | two (xs, yys as SOME (y, ys), zzs as SOME (z, zs)) =
    if y <= z then
      two (z :: xs, yys, step zs)
    else
      two (y :: xs, step ys, zzs)

fun start xs = step (Many xs :: nil)
fun merge (xs, ys) = two (nil, start xs, start ys)
