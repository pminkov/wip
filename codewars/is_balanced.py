import test

def is_balanced(s, caps):
  openers = []
  for c in s:
    ci = caps.find(c)
    if ci != -1:
      if ci % 2 == 0:
        if caps[ci + 1] == caps[ci]:
          # Same character, greedily close.
          if len(openers):
            if openers[-1] == c:
              openers.pop()
            else:
              openers.append(c)
          else:
            openers.append(c)
        else:
          openers.append(c)
      else:
        opp = caps[ci - 1]
        if len(openers) and openers[-1] == opp:
          openers.pop()
        else:
          return False

  return len(openers) == 0


test.assert_equals(is_balanced("Sensei says -yes-!", "--"), True)
test.assert_equals(is_balanced("(Sensei says yes!)", "()"), True)
test.assert_equals(is_balanced("(Sensei says no!", "()"), False)
test.assert_equals(is_balanced("(Sensei [says] yes!)", "()[]"), True)
test.assert_equals(is_balanced("(Sensei [says) no!]", "()[]"), False)
test.assert_equals(is_balanced("Sensei -says no!", "--"), False)

