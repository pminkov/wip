class Node:
  def __init__(self, value):
    self.prev = None
    self.next = None
    self.value = value

class LinkedList:
  def __init__(self):
    self.head = None
    self.tail = None
    self.size = 0

  def insert(self, value):
    if self.head == None:
      self.head = Node(value)
      self.tail = self.head
    else:
      new_tail = Node(value)
      new_tail.prev = self.tail
      self.tail.next = new_tail
      self.tail = new_tail

    self.size += 1
    return self.tail

  def removeHead(self):
    if self.head == self.tail:
      del self.head
      self.head = self.tail = None
      self.size -= 1
    elif self.head:
      self.head = self.head.next
      self.head.prev = None
      self.size -= 1
    else:
      return


  def printList(self):
    if self.head == None:
      print 'Empty list.'
    else:
      cur = self.head
      while cur != None:
        print '[',
        print cur, 
        print cur.value,
        print ']'
        cur = cur.next
      print

  def promoteToTail(self, node):
    tmp = self.tail.value
    self.tail.value = node.value
    node.value = tmp

    return (node, self.tail)

KEY = 0
VALUE = 1
DEBUG = 1

class LRUCache:
  def __init__(self, capacity):
    self.queue = LinkedList()
    self.key_to_node = {}
    self.capacity = capacity

    if DEBUG:
      print 'Initialized cache.'
      self.printCache()

  def printCache(self):
    print '==== CACHE:'
    for (k, v) in self.key_to_node.items():
      print k, v
    print 'Queue:'
    self.queue.printList()
    print

  def _touch_key(self, key):
    # Promote node to top.
    assert key in self.key_to_node
    (node, tail) = self.queue.promoteToTail(self.key_to_node[key])

    self.key_to_node[node.value[KEY]] = node
    self.key_to_node[tail.value[KEY]] = tail


  def set(self, key, value):
    if key in self.key_to_node:
      self._touch_key(key)
      self.key_to_node[key].value = (key, value)
    else:
      if self.queue.size == self.capacity:
        head_key = self.queue.head.value[KEY]
        self.queue.removeHead()
        del self.key_to_node[head_key]

      node = self.queue.insert((key, value))
      self.key_to_node[key] = node

      assert len(self.key_to_node) <= self.capacity

    if DEBUG:
      print 'Setting', key, ' = ', value
      self.printCache()


  def get(self, key):
    ret = None
    if key in self.key_to_node:
      self._touch_key(key)
      ret = self.key_to_node[key].value[VALUE]

    if DEBUG:
      print 'Getting', key, '. Result = ', ret
      self.printCache()

    return ret

if __name__ == '__main__':
  cache = LRUCache(3)

  cache.set(5, "five")
  cache.set(2, "two")
  assert cache.get(5) == "five"
  cache.set(7, "seven")
  cache.set(8, "eight")
  cache.set(9, "nine")
  assert cache.get(9) == "nine"
  assert cache.get(100) == None
  cache.set(7, 'SEVEN')
  assert cache.get(8) == 'eight'
  assert cache.get(7) == 'SEVEN'
