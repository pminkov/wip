import test

OPEN = '([{'
OPP = { '}': '{', ')': '(', ']': '[' }


def group_check(s):
  openers = []
  for c in s:
    if c in OPEN:
      openers.append(c)
    else:
      opp = OPP[c]
      if len(openers) and openers[-1] == opp:
        openers.pop()
      else:
        return False
  return len(openers) == 0

test.assert_equals(group_check("()"), True)
test.assert_equals(group_check("({"), False)
test.assert_equals(group_check("[[]"), False)
test.assert_equals(group_check("[]"), True)
test.assert_equals(group_check("{[][]}"), True)
test.assert_equals(group_check("{{{{"), False)
test.assert_equals(group_check("[][]((([])))"), True)
      
      
