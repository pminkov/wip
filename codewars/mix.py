import test

from collections import defaultdict

def count(s):
  c = defaultdict(int)
  for x in s:
    if x >= 'a' and x <= 'z':
      c[x] += 1
  return c

def mix(s1, s2):
  c1 = count(s1)
  c2 = count(s2)
  letters = set(c1.keys() + c2.keys())
  answer = []
  for let in letters:
    k1 = c1[let]
    k2 = c2[let]
    if k1 > 1 or k2 > 1:
      if k1 > k2:
        answer.append('1:%s' % (let * k1))
      elif k1 < k2:
        answer.append('2:%s' % (let * k2))
      else:
        answer.append('=:%s' % (let * k1))

  answer = sorted(answer, key=lambda x: (-len(x), x))
  return '/'.join(answer)
  
      

test.assert_equals(mix("Are they here", "yes, they are here"), "2:eeeee/2:yy/=:hh/=:rr")
test.assert_equals(mix("looping is fun but dangerous", "less dangerous than coding"), "1:ooo/1:uuu/2:sss/=:nnn/1:ii/2:aa/2:dd/2:ee/=:gg")
test.assert_equals(mix(" In many languages", " there's a pair of functions"), "1:aaa/1:nnn/1:gg/2:ee/2:ff/2:ii/2:oo/2:rr/2:ss/2:tt")
test.assert_equals(mix("Lords of the Fallen", "gamekult"), "1:ee/1:ll/1:oo")
test.assert_equals(mix("codewars", "codewars"), "")
test.assert_equals(mix("A generation must confront the looming ", "codewarrs"), "1:nnnnn/1:ooooo/1:tttt/1:eee/1:gg/1:ii/1:mm/=:rr")
