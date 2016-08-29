import test

def same_structure_as(a, b):
  if type(a) != type(b) or len(a) != len(b):
    return False
  else:
    ok = True
    for i in range(0, len(a)):
      if type(a[i]) == list:
        ok = ok and same_structure_as(a[i], b[i])

    return ok

test.assert_equals(same_structure_as([1,[1,1]],[2,[2,2]]), True, "[1,[1,1]] same as [2,[2,2]]")
test.assert_equals(same_structure_as([1,[1,1]],[[2,2],2]), False, "[1,[1,1]] not same as [[2,2],2]")
      
