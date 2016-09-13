
def spiralize(size):
  a = []
  for i in range(0, size):
    a.append([0] * size)

  d = 0
  sz = size

  for i in range(d, d + sz):
    a[d][i] = 1
    a[i][d] = 1



  for x in range(0, len(a)):
    print a[x]

spiralize(10)
