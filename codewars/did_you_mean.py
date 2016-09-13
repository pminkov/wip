from math import min

def edit_dist(sa, sb, ai, bi):
  if ai == len(sa):
    return len(sb) - bi
  if bi == len(sb):
    return len(sa) - ai
  
  a = sa[ai:]
  b = sb[bi:]

  minv = 1 << 20

  if a[0] == b[0]:
    minv = min(minv, edit_dist(sa, sb, ai + 1, bi + 1))

  e1 = 1 + edit_dist(sa, sb, ai + 1, bi)
  e2 = 1 + edit_dist(sa, sb, ai, bi + 1)

  return min(minv, min(e1, e2))


print edit_dist("pet", "ke", 0, 0)

