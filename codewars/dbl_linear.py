import test

def f2(x): return x * 2 + 1
def f3(x): return x * 3 + 1


def dbl_linear(n):
  ar = [1]
  pos2 = 0
  pos3 = 0

  cp = 0

  while cp < n:
    c2 = f2(ar[pos2])
    c3 = f3(ar[pos3])

    if c2 < c3:
      chosen = c2
      pos2 += 1
    else:
      chosen = c3
      pos3 += 1

    if chosen > ar[-1]:
      ar.append(chosen)
      cp += 1

  return ar[cp]
        

def testing(actual, expected):
        test.assert_equals(actual, expected)

testing(dbl_linear(10), 22)
testing(dbl_linear(20), 57)
testing(dbl_linear(30), 91)
testing(dbl_linear(50), 175)
