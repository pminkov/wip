
class HeapElem:
  def __init__(self, key):
    self.key = key
    self.use_count = 1

  def __str__(self):
    return 'k:{} {}'.format(self.key, self.use_count)

class LFUCache:
  def __init__(self, capacity):
    self.capacity = capacity
    self.heap = [None]
    self.key_to_pos = {}
    self.key_to_value = {}


  def add(self, key, value):
    if len(self.heap) - 1 == self.capacity:
      self.remove_top()

    self.heap.append(HeapElem(key))
    pos = len(self.heap) - 1

    while pos / 2 >= 1:
      parent_pos = pos / 2
      
      if self.heap[parent_pos].use_count > self.heap[pos].use_count:
        self.heap[parent_pos], self.heap[pos] = self.heap[pos], self.heap[parent_pos]
        pos = parent_pos
        self.key_to_pos[ self.heap[pos].key ] = pos
      else:
        break

    self.key_to_pos[key] = pos
    self.key_to_value[key] = value

  def remove_top(self):
    key = self.heap[1].key

    del self.key_to_value[key]
    del self.key_to_pos[key]

    if len(self.heap) == 2:
      self.heap.pop()
      return

    self.heap[1] = self.heap[len(self.heap) - 1]
    self.heap.pop()

    self.key_to_pos[ self.heap[1].key ] = 1

    # At this point, array, dicts are good. Heap is not.
    self.move_down(1)
    
  def move_down(self, pos):
    N = len(self.heap) - 1

    while True:
      c = []
      c.append(pos * 2)
      c.append(pos * 2 + 1)
      
      swapped = False
      for ci in c:
        if ci <= N and self.heap[pos].use_count > self.heap[ci].use_count:
          self.heap[pos], self.heap[ci] = self.heap[ci], self.heap[pos]
          self.key_to_pos[ self.heap[pos].key ] = pos
          pos = ci
          swapped = True
          break

      if not swapped:
        break

    self.key_to_pos[ self.heap[pos].key ] = pos


  def get(self, key):
    if not key in self.key_to_pos:
      return None

    pos = self.key_to_pos[key]
    self.heap[pos].use_count += 1
    self.move_down(pos)

    return self.key_to_value[key]

  def verify(self):
    N = len(self.heap) - 1
    for pos in range(1, N + 1):
      c = []
      c.append(pos * 2)
      c.append(pos * 2 + 1)
      for ci in c:
        if ci <= N:
          assert self.heap[pos].use_count <= self.heap[ci].use_count
      assert self.heap[pos] == self.heap[ self.key_to_pos[ self.heap[pos].key ] ]

  def dump(self, msg=''):
    print 'DUMP - {}'.format(msg)
    print 'Heap:', [str(x) for x in self.heap]
    print 'Key2Pos:', self.key_to_pos
    print 'Key2Value:', self.key_to_value

if __name__ == '__main__':
  cache = LFUCache(3)
  cache.dump()
  cache.add(5, "five")
  cache.dump()
  cache.add(6, "six")
  cache.dump()
  cache.add(7, "seven")
  cache.dump()

  cache.verify()

  cache.get(5)
  cache.get(6)
  cache.get(6)
  cache.get(6)
  cache.get(6)
  for x in range(0, 10):
    cache.get(7)
  cache.verify()

  cache.dump()

  cache.dump("Before adding one")
  cache.add(1, "one")
  cache.dump("After adding one")
  
  cache.remove_top()
  cache.remove_top()

  cache.dump()
  cache.verify()
