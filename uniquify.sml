fun inner (x, nil, ys, zs) = (rev ys, x :: zs)
  | inner (x, y :: xs, ys, zs) =
    if x = y then
      inner (x, xs, ys, zs)
    else
      inner (x, xs, y :: ys, zs)

fun outer (x, xs, ys) =
  case inner (x, xs, nil, ys) of
      (nil, ys) => rev ys
    | (x :: xs, ys) => outer (x, xs, ys)

fun uniquify nil = nil
  | uniquify (x :: xs) = outer (x, xs, nil)
