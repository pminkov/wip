def pascal(p, x=[1]):
  return [x] if p == 1 else [x] + pascal(p-1, [1] + [x[i] + x[i + 1] for i in range(0, len(x)-1)] + [1])
