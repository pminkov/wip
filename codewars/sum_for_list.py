import test

from collections import defaultdict

import math

def sum_for_list(lst):
  psum = defaultdict(int)

  for x in lst:
    sx = x

    if x < 0: x = -x

    while True:
      div_found = False

      i = 2 
      while i * i <= x:
        if x % i == 0:
          div_found = True
          psum[i] += sx
          while x % i == 0:
            x = x / i
          break
        i += 1

      if not div_found:
        if x != 1:
          psum[x] += sx
        break

  return [list(x) for x in sorted(psum.items())]

          

 
a = [12, 15]
test.assert_equals(sum_for_list(a), [[2, 12], [3, 27], [5, 15]])
