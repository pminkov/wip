#!/bin/python

def dig_sum(a):
  ret = 0
  while a != 0:
    ret += a % 10
    a /= 10
  return ret

def compare(a, b):
  """1 if a is better than b"""
  da = dig_sum(a)
  db = dig_sum(b)
  if da > db:
    return 1
  elif da < db:
    return -1
  else:
    if a < b:
      return 1
    elif a > b:
      return -1
    else:
      return 0
  

if __name__ == '__main__':
  n = int(raw_input().strip())
  divs = []
  for i in range(1, n+1):
    if n % i == 0:
      divs.append(i)

  print sorted(divs, cmp=compare)[-1]
