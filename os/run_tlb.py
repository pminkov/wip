import subprocess
import os


def run_tlb(array_size):
  print 'Running for %d ...' % array_size
  out = subprocess.check_output(["./tlb", str(array_size)])
  lines = out.split('\n')
  timing = filter(lambda x: 'nanoseconds' in x, lines)[0]
  timing = float(timing[timing.find(':') + 2: ])
  print 'Aaand done: %.5f' % timing
  return timing

def linear_run(start, end, resolution):
  timings = []
  step = (end - start) / resolution
  for i in range(start, end, step):
    ti = run_tlb(i)
    timings.append((i, ti))

  print timings


def exponential_run(iters=10):
  start_size = 10

  timings = []
  for i in range(0, iters):
    sz = start_size * (1 << i)
    ti = run_tlb(sz)
    timings.append((sz, ti))

  print timings
    

if __name__ == '__main__':
  #linear_run(400, 3200, 40)
  exponential_run(10)

