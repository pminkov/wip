import sys

class TrieNode:
  def __init__(self):
    self.edges = {}
    self.count = 0
    

class Trie:
  def __init__(self):
    self.root = TrieNode()


  def add(self, text):
    cur_node = self.root

    for char in text:
      if char in cur_node.edges:
        cur_node = cur_node.edges[char]
      else:
        new_node = TrieNode()
        cur_node.edges[char] = new_node
        cur_node = new_node

      cur_node.count += 1


  def find(self, text):
    cur_node = self.root

    for char in text:
      if char in cur_node.edges:
        cur_node = cur_node.edges[char]
      else:
        return 0

    return cur_node.count
    

def line():
  return sys.stdin.readline().strip()

if __name__ == '__main__':
  cmds = int(line())

  trie = Trie()

  for ci in range(cmds):
    cmd = line()
    if cmd.startswith('add'):
      trie.add(cmd[4:])
    else:
      res = trie.find(cmd[5:])
      print res
      
  
