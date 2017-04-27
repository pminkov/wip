rules = {}

def rec(part, words):
  if part in 'NVD':
    if len(words) == 1:
      for ww in rules[part]:
        if ww.lower() == words[0].lower():
          return 1

      return 0
    else:
      return 0
  else:
    ret = 0
    for rule in rules[part]:
      sub_rules = rule.split()
      n = len(words)

      if len(sub_rules) == 1:
        ret += rec(sub_rules[0], words)

      elif len(sub_rules) == 2:
        for sp in range(1, n):
          r0 = rec(sub_rules[0], words[0:sp]) 
          r1 = rec(sub_rules[1], words[sp:n])
          ret += r0 * r1

      elif len(sub_rules) == 3:
        for sp1 in range(1, n - 1):
          for sp2 in range(sp1+1, n):
            r0 = rec(sub_rules[0], words[0:sp1]) 
            r1 = rec(sub_rules[1], words[sp1:sp2])
            r2 = rec(sub_rules[2], words[sp2:n])
            ret += r0 * r1 * r2

      else:
        assert(False)

    return ret

def count(sent):
  words = sent.split()

  res = rec('S', words)

  return res

def init_rules():
  rules['S'] = ['NP VP']
  rules['NP'] = ['N', 'D N', 'N N', 'N N N']
  rules['VP'] = ['V NP', 'V', 'V NP NP']
  rules['N'] = ['interest', 'Fed', 'rates', 'raises']
  rules['V'] = ['interest', 'rates', 'raises']
  rules['D'] = ['the', 'a']

init_rules()

s1 = 'The Fed raises interest rates'
s2 = 'The Fed raises raises'
s3 = 'raises raises interest raises'

sents = [s1, s2, s3]

for s in sents:
  c = count(s)
  print c, s


