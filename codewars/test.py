index = 0

def assert_equals(a, b, desc = ""):
  global index
  index += 1
  assert a == b, "[%d] a=%s b=%s" % (index, a, b)
