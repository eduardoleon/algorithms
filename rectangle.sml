fun right (m, n, xs) = if m = 0 then NONE else SOME (m-1, n, #"R" :: xs)
fun down (m, n, xs) = if n = 0 then NONE else SOME (m, n-1, #"D" :: xs)

fun loop (xs, nil) = xs
  | loop (xs, s :: ss) =
    case (right s, down s) of
        (NONE, NONE) => loop (implode (#3 s) :: xs, ss)
      | (SOME s, NONE) => loop (xs, s :: ss)
      | (NONE, SOME s) => loop (xs, s :: ss)
      | (SOME s, SOME t) => loop (xs, s :: t :: ss)

fun paths (m, n) = loop (nil, (m, n, nil) :: nil)
