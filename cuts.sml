fun loop (0, _, _, _, d) = d
  | loop (n, a, b, c, d) = loop (n - 1, b, c, d, a + d)

fun cuts n = if n < 0 then 0 else loop (n, 0, 0, 0, 1)
