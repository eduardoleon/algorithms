#include <stdio.h>

int f(int n)
{
     if (n < 0) return 0;
     
     int a = 0, b = 0, c = 0, d = 0, e = 1;
     
     while (n--) {
          a = b;
          b = c;
          c = d;
          d = e;
          e = a + d;
     }
     
     return e;
}

int main()
{
     for (int n = 0; n < 69; n++) {
          int fn = f(n);
          printf("f(%d) = %d\n", n, fn);
     }
}
