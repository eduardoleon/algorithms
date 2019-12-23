datatype 'a tree = Empty | Tree of 'a tree * 'a * 'a tree
datatype 'a step = Small of 'a | Large of 'a tree

fun visit (_, nil) = true
  | visit (c, Small x :: ss) = if x > c then visit (x, ss) else false
  | visit (c, Large Empty :: ss) = visit (c, ss)
  | visit (c, Large (Tree (a,x,b)) :: ss) = visit (c, Large a :: Small x :: Large b :: ss)

fun is_bst (c, xs) = visit (c, Large xs :: nil)

val good = Tree (Tree (Empty, 2, Tree (Empty, 4, Empty)), 5, Empty)
val bad = Tree (Tree (Empty, 2, Tree (Empty, 7, Empty)), 5, Empty)
