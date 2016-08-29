import test

def remove_comments(line, comments):
  for c in comments:
    pos = line.find(c)
    if pos != -1:
      line = line[: pos]
  return line.rstrip()

def solution(string, markers):
  lines = string.split('\n')
  lines_nc = map(lambda s: remove_comments(s, markers), lines)
  ret = '\n'.join(lines_nc)
  return ret


test.assert_equals(solution("apples, pears # and bananas\ngrapes\nbananas !apples", ["#", "!"]), "apples, pears\ngrapes\nbananas")
test.assert_equals(solution("a #b\nc\nd $e f g", ["#", "$"]), "a\nc\nd")
