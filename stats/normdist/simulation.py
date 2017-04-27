#!/usr/bin/python

# Verify that the sum of N random integers in the [0,1] range
# forms a normal distribution. Copy the output and plot it in
# Octave.

import random

if __name__ == '__main__':
  print "generating..."

  count = [0] * 101

  N = 5000
  for i in range(1, N):
    sum = 0
    for j in range(1, 100):
      sum = sum + random.randint(0, 1)
    count[sum] += 1 

  print count
