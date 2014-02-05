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


# Mean and confidence interval at 95% for an array of numbers "x"
def ci(x):
  mean_value = mean(x)
  ci = 1.96 * math.sqrt( var(x) / len(x) )
  return (mean_value, ci)


def ci_from_stddev(n, stddev):
  ci = 1.96 * math.sqrt ((stddev * stddev) / float(n))
  return ci


def diff_normal_distrib(mean1, s1, mean2, s2):
  return (mean1 - mean2, math.sqrt(s1 * s1 + s2 * s2))


def binomial_ci(n, prob):
  """Confidence interval on the mean of N coin flips on a
    coin with head probability of prob
  """
  return 1.96 * math.sqrt(prob * (1 - prob) / float(n))


def in_ci(x1, ci, x2):
  return x1 - ci <= x2 and x2 <= x1 + ci


def AB_test(n_observations, conversion_rate_1, conversion_rate_2):
  """Computes AB test significance.

  conversion_rate_1, 2 are percents.
  """

  # Convert to probability range, so that we can estimate CI - [0, 1].
  conversion_rate_1 = conversion_rate_1 / 100.
  conversion_rate_2 = conversion_rate_2 / 100.

  # Find confidence interval for case A.
  ci = binomial_ci(n_observations, conversion_rate_1)

  return not in_ci(conversion_rate_1, ci, conversion_rate_2)


def verify_ci():
  mu = 16
  sigma = 3

  N = 250
  S = 1000 

  ci = 1.96 * math.sqrt(sigma * sigma / float(N))

  print "Mean =", mu
  print "Standard deviation =", sigma
  print "Size of sample =", N
  print "Number of times we sample =", S
  print "CI =", ci


  in_ci = 0

  for i in range(0, S):
    x = [random.gauss(mu, sigma) for j in range(0, N)]
    mv = mean(x)
    if i <= 10:
      print (mv)
    if (mu - ci <= mv) and (mv <= mu + ci):
      in_ci += 1

  # We expect 95%
  print "Percent of times the mean is in the 95% confidence interval: ", \
      (100. * in_ci / float(S))

if __name__ == '__main__':
  print(AB_test(10000000, 1, 1.01))









