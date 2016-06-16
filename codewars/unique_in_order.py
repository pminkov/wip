import test

def unique_in_order(iterable):
  prev = None
  final = []
  for x in iterable:
    if x != prev:
      final.append(x)
      prev = x

  return final

test.assert_equals(unique_in_order('AAAABBBCCDAABBB'), ['A','B','C','D','A','B'])


