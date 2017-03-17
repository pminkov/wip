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

def binomial_ci_print(trials, positive):
  prob = float(positive) / trials

  ci = binomial_ci(trials, prob)

  print "We did %d trials" % trials
  print "%.2f%% of these were positive" % (100. * prob)
  print "We're 95%% sure that the probability is between %f and %f" % (100. * (prob - ci), 100*(prob + ci))

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

def correlation(x, y):
  assert(len(x) == len(y))

  mx = mean(x)
  my = mean(y)

  cov = 0.0
  vx = 0.0
  vy = 0.0

  print (mx, my)

  for i in range(0, len(x)):
    cov += (x[i] - mx) * (y[i] - my)
    vx += (x[i] - mx) ** 2
    vy += (y[i] - my) ** 2

  print cov, vx, vy

  return cov / math.sqrt(vx * vy)

class BivariateGaussian:
  def __init__(self, mu, sigma):
    self.mu = mu
    self.sigma = sigma

  def debug_print(self):
    print "%.3f %.3f %.3f" % (self.mu[0], self.sigma[0][0], self.sigma[0][1])
    print "%.3f %.3f %.3f" % (self.mu[1], self.sigma[1][0], self.sigma[1][1])

def bivariate_from_sample(x, y):
  """http://en.wikipedia.org/wiki/Multivariate_normal_distribution"""
  
  mx = mean(x)
  my = mean(y)
  cor = correlation(x, y)
  sx = stddev(x)
  sy = stddev(y)

  mu = [mx, my]
  sigma00 = sx ** 2
  sigma01 = cor * sx * sy 
  sigma10 = sigma01
  sigma11 = sy ** 2
  sigma = [[sigma00, sigma01], [sigma10, sigma11]] 

  return BivariateGaussian(mu, sigma)

def xy_mean(x, y):
  assert(len(x) == len(y))
  s = sum([a * b for a, b in zip(x, y)])
  s = s / float(len(x))
  return s

def covariance(x, y):
  assert(len(x) == len(y))

  cov = 0.0
  mx = mean(x)
  my = mean(y)
  for i in range(0, len(x)):
    cov += (x[i] - mx) * (y[i] - my)

  return cov

def test_bivariate():
  # Generated from R.
  # library(MASS)
  # bivn <- mvrnorm(100, mu = c(0, 0), Sigma = matrix(c(1, .5, .5, 1), 2))

  x = [-1.330445,2.624708,0.3175569,1.003661,0.9067273,1.291717,0.9540802,-1.084079,-1.316728,2.124587,-0.4714208,-0.1755755,-1.038468,0.9487485,0.4593007,-0.6127964,-2.445682,3.224693,-0.4420146,0.1632684,1.080131,0.487083,0.6126686,-1.379246,-0.506322,0.2351168,1.218001,0.02740395,-1.338133,0.052684,1.984915,2.182968,2.516678,0.7095957,-0.5322837,0.9826579,0.8286406,-0.629734,-2.485136,-0.8902261,1.862981,1.371093,-1.274282,-0.03900223,0.5899871,1.396497,1.527002,-0.7219348,-0.7880412,-1.851815,-0.3495747,-0.04982129,1.190869,0.5889345,0.05236714,0.8084072,-0.3277964,1.108178,-1.17517,-1.630058,-0.2966483,0.4375192,-0.4309936,-1.777083,-0.3727264,-0.100522,-1.047886,1.403851,-0.2065635,-0.3314062,1.152139,0.831774,-1.292925,-0.6989879,0.4877748,-0.1607452,-0.8015476,0.9028863,-0.5049121,-1.163795,-1.882677,0.6191456,-1.274601,-1.063154,1.580944,-0.03053819,-2.287732,-0.07759776,0.7584942,0.6916248,-2.145091,-0.525472,-1.607396,0.6669768,-0.6499871,-0.6441185,0.02415668,1.231003,0.8918369,-1.02303]

  y = [-0.07619918,0.9512259,0.2062551,0.4109501,0.5973822,-0.6956448,1.113002,-1.940244,0.1356901,2.094121,-0.3341403,0.2447469,0.1998984,1.584152,0.5051048,-1.687059,-0.4168003,2.995849,-0.9473457,-0.2409975,2.998109,0.1384147,0.020827,-1.733687,0.8163241,0.08999753,1.352944,-0.4092946,-0.8208461,0.5185806,3.095147,0.6733931,2.167403,0.03815116,0.2482966,0.2307691,1.623428,-1.0552,-1.163669,0.4262521,0.5418255,0.9588541,-1.018745,1.142185,-0.2059212,-0.4476011,1.599265,0.05938128,-0.1188557,-1.009806,-0.0257042,0.2229756,0.1408087,0.2476248,-0.8851502,0.831636,-0.4308914,1.928286,-0.4539003,-1.5081,0.4690905,-0.2974782,-0.9685858,-2.20916,0.3491061,1.529957,0.450593,1.035549,0.03790698,0.2896971,0.9748086,2.338396,0.8248044,-0.5779647,-0.3458136,-0.4624065,1.744647,-1.003243,-0.4035296,-1.738525,-0.8996269,1.412175,0.3946643,-0.2284818,0.2660545,1.06881,-1.714902,0.7535476,-0.3863818,0.4442646,-1.494763,-1.67595,-0.4036348,-1.294588,-0.197635,0.5826248,1.918146,0.3011083,0.04759478,1.464771]

  bg = bivariate_from_sample(x, y)
  bg.debug_print()

if __name__ == '__main__':
  ci = ci_from_stddev(100, 0.5)

  print(1.05 - ci, 1.05 + ci)

  









