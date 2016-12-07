import math

if __name__ == '__main__':
  div = math.pi / 2

  res = sorted([('%.6f' % math.sin(x), x) for x in range(0, 100000)])
  for i in range(0, len(res) - 1):
    if res[i][0] == res[i + 1][0]:
      print res[i]
      print res[i + 1]

