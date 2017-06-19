"""
Check if a graph has a cycle.

Run a DFS and see if there's a back edge pointing to a node that's on the DFS stack.

Trickiest part here is to prove that you can run the starting from any vertex, until you
have vertices that you haven't visited. If there's a cycle in the graph, you can discover
it starting from any vertex in it. If you start from a vertex and reach a vertex that's
in a cycle, you'll discover that cycle.
"""

from collections import defaultdict

class Graph:
  def __init__(self):
    self.edges = defaultdict(list)
    self.N = 0

  def add_edge(self, u, v):
    self.edges[u].append(v)
    self.N = max(self.N, max(u, v))

  def add_edges(self, li):
    for (u, v) in li:
      self.add_edge(u, v)

  def printCycle(self, path, vert):
    print 'CYCLE:',
    start = False
    for v in path:
      if v == vert:
        start = True

      if start:
        print v, ' -> ',

    print vert
    

  def dfs(self, u, path):
    self.visited[u] = True
    
    path.add(u)

    for v in self.edges[u]:
      if v in path:
        self.printCycle(path, v)
        return True 

      if not self.visited[v]:
        found_cycle = self.dfs(v, path)
        if found_cycle:
          return True

    path.remove(u)

    return False

  def check_for_cycle(self):
    self.visited = [False] * (self.N+1)

    found_cycle = False
    for u in range(1, self.N+1):
      if not self.visited[u]:
        path = set()

        found_cycle = self.dfs(u, path)
        if found_cycle:
          break

    if not found_cycle:
      print 'No cycle'
      

g = Graph()
g.add_edges([(1,2), (1,3), (3,2), (4,3), (2,4), (4,5)])
g.check_for_cycle()

"""OUTPUT:

$ python ./has_cycle.py 
CYCLE: 2  ->  3  ->  4  ->  2
"""
