
def isop(x):
  return x in '+-*/'

def apply(a, b, x):
  if x == '+':
    return a + b
  elif x == '-':
    return a - b
  elif x == '*':
    return a * b
  elif x == '/':
    return a / b

# reverse polish
def calc(expr):
  expr = expr.split()
  st = []
  for x in expr:
    if isop(x):
      o2 = st.pop()
      o1 = st.pop()
      r = apply(o1, o2, x)
      st.append(r)
    else:
      st.append(float(x))
  if len(st) == 0:
    return 0
  else:
    return st[-1]
    
    
print calc("5 1 2 + 4 * + 3 -")
