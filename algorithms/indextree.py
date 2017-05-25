"""
Index Tree
==========

An index tree of size N allows the following operations:

Update(index, value) - Add "value" to its index element. O(logN)
Query(to) - Return the sum of all elements from 0 to to. O(logN)

You can trivially update it to support range queries.

The idea is that the first node contains the sum of all elements.
Its left child contains the sum of the first half, its right child the sum
of the second half. And so on, recursively.
"""
import random

class IndexTree:
  def __init__(self, capacity):
    nodes_at_level = 1
    total_nodes = 0
    while nodes_at_level < capacity:
      total_nodes += nodes_at_level
      nodes_at_level *= 2

    total_nodes += nodes_at_level
    print 'Nodes at final level: %d' % nodes_at_level
    print 'Total nodes: %d' % total_nodes

    self.tree_width = nodes_at_level
    self.ar = [0] * (total_nodes + 1)
    assert len(self.ar) == self.tree_width * 2


  def update(self, index, value):
    node = 1
    width = self.tree_width

    while width:
      self.ar[node] += value

      mid = width / 2
      if index < mid:
        node = node * 2
      else:
        node = node * 2 + 1
        index -= mid

      width /= 2

  def query(self, to):
    """Sums elements in range [0, to].
    """

    node = 1
    width = self.tree_width
    ans = 0

    while width >= 2:
      mid = width / 2
      if to < mid:
        node = node * 2
      else:
        ans += self.ar[node * 2]
        node = node * 2 + 1
        to -= mid

      width /= 2

    assert width == 1
    ans += self.ar[node]

    return ans

  def printTree(self):
    nodes = [1]
    width = self.tree_width

    while width:
      for node in nodes:
        vv = '[ %-5d]' % self.ar[node]
        print vv,
        for i in range(width - 1):
          print '-' * 8,
      print
      newnodes = []
      for node in nodes:
        newnodes.append(node * 2)
        newnodes.append(node * 2 + 1)
      nodes = newnodes

      width /= 2
      

def test(capacity):
  t = IndexTree(capacity)
  naive = [0] * capacity

  for i in range(0, 1000):
    idx = random.randrange(capacity)
    value = random.randint(0, 10)
    naive[idx] += value
    t.update(idx, value)

    to = random.randrange(capacity)
    ans = 0
    for j in range(0, to + 1):
      ans += naive[j]

    assert ans == t.query(to)

      
t = IndexTree(7)
t.update(3, 2)
t.update(7, 100)
t.update(2, 200)
t.update(5, 60)
t.printTree()

for i in range(0, 8):
  print i, t.query(i)

test(2000)

