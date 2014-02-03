"""Various Statistics routines"""

import math
import random

def n_flips(n):
  return [random.randrange(2) for i in xrange(0, n)]

def mean(x):
  sum = 0.0
  for i in xrange(0, len(x)): sum += x[i]
  return sum / len(x)

def var(x):
  mean_x = mean(x)
  v = 0.0
  for i in xrange(0, len(x)): v += (mean_x - x[i]) ** 2
  v /= len(x)
  return v

def stddev(x):
  return math.sqrt(var(x))

def fact(n):
  if n <= 1: return 1
  else: return n * fact(n - 1)

def comb(n, k):
  return fact(n) / (fact(k) * fact(n - k))

def mean_n_flipcoins(n):
  mean = 0.0
  
  prob_flip = 1. / (2 ** n)
  for i in range(1, n+1):
    mean += comb(n, i) * prob_flip * i

  return mean

def binom_prob(n, k, p):
  """Probability of selecting k out of n where each selection is with probability p"""
  return comb(n, k) * (p**k) * ((1-p)**(n-k))

def simulate_flips():
  s = []

  for i in range(0, 10000):
    fli = n_flips(10)

    x = mean(fli)

    if i < 100:
      print(x)
    elif i == 100:
      print("...")

    s.append(x)

  print (var(s))

if __name__ == '__main__':
  for i in range(0, 15):
    print("%d %.5f" % ((i+1), binom_prob(15, (i+1), 0.9)))







