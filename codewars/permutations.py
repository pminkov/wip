from collections import defaultdict

def gen(counts, cur = ''):
  keys = counts.keys()

  done = True
  ret = []
  for k in keys:
    if counts[k] > 0:
      done = False
      counts[k] -= 1
      ret += gen(counts, cur + k)
      counts[k] += 1

  if done:
    return [cur]
  else:
    return ret

def permutations(x):
  counts = defaultdict(int)
  for c in x:
    counts[c] += 1

  ret = gen(counts)
  return ret


permutations('aaabb')

    
    
