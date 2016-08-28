import re
import test
from collections import defaultdict

def parse_term(x):
  sp = re.search(r'[a-z]', x).start()
  coef, vars = (x[:sp], x[sp:])
  if coef == '+' or not coef: coef = '1'
  if coef == '-': coef = '-1'
  return (0 if coef == '' else int(coef), ''.join(sorted(vars)))

def simplify(x):
  x = x.replace('+', ' +').replace('-', ' -').split()

  sums = defaultdict(int)

  for part in x:
    (coef, vars) = parse_term(part)
    sums[vars] += coef

  def compare(x, y):
    x = x[0]
    y = y[0]
    if len(x) == len(y):
      if x == y: return 0
      elif x > y: return 1
      elif x < y: return -1
    else:
      return len(x) - len(y)

  def term(x):
    if x[1] == 1: coef = '+'
    elif x[1] == -1: coef = '-'
    elif x[1] > 1: coef = '+' + str(x[1])
    else: coef = str(x[1])
    return coef + x[0]

  clean = filter(lambda x: x[1] != 0, sorted(sums.items(), cmp=compare))
  ret = ''.join(map(term, clean))
  if ret.startswith('+'): ret = ret[1:]
  return ret

test.assert_equals(simplify("dc+dcba"), "cd+abcd")
test.assert_equals(simplify("2xy-yx"),"xy")
test.assert_equals(simplify("-a+5ab+3a-c-2a"),"-c+5ab")
test.assert_equals(simplify("-abc+3a+2ac"),"3a+2ac-abc")
test.assert_equals(simplify("xyz-xz"),"-xz+xyz")
test.assert_equals(simplify("a+ca-ab"),"a-ab+ac")
test.assert_equals(simplify("xzy+zby"),"byz+xyz")
test.assert_equals(simplify("-y+x"),"x-y")
test.assert_equals(simplify("y-x"),"-x+y")
