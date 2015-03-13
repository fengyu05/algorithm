"""
Common function use in graph
"""
import unittest
import math

"""
For sparse graph
"""
class Graph:
  """
  Create a graph with n node [0, n)
  """
  def __init__(self, n):
    self.n = n
    self.adjacents = [list() for x in xrange(n)]

  """
  Insert a edit x->y
  """
  def insert(self, x, y):
    self.adjacents[x].append(y)

  def insertList(self, x, nodeList):
    for y in nodeList:
      self.adjacents[x].append(y)

  def remove(self, x, y):
    self.adjacents[x].remove(y)

  def hasEdge(self, x, y):
    return self.adjacents[x].count(y) > 0

  def toString(self):
    for x in xrange(self.n):
      print x, ":", self.adjacents[x]

  """
  A DFS to collect as much as information of a graph
  degree[]: degree of a node
  edge[][]: edge type 
         0:no edge
         1:tree (a edge from parent to a child in a tree)
         2:back (a edge from a node to its ancestor in a tree)
         3:down (a edge from two diffient branch, the current visit first)
         4:cross (a edge from tow diffient branch, the current visit late)
  start[]: start index of visit a node
  finish[]: finish index of visit a node
  parent[]: parent node
  lowIndex[]: represents the smallest index of any node known to be reachable from
         (including itself)
         lowIndex[u] = start[u]
         lowIndex[u] = min(lowIndex[u], lowIndex[v])  when u->v
  """
  def generalDFS(self):
    class Env:
      def __init__(self, n):
        self.index = 0
        self.edge = [[0] * n] * n #TODO store it in a spare way
        self.degree = [0] * n
        self.start = [0] * n
        self.finish = [0] * n
        self.index = 0
        self.lowIndex = [0] * n
        self.parent = [-1] * n

    env = Env(self.n)

    def dfs(u, env):
      env.index += 1
      env.start[u] = env.lowIndex[u] = env.index
      for v in self.adjacents[u]:
        if env.start[v] == 0: #found an untouched node
          env.edge[u][v] = 1 #a tree edge
          env.degree[u] += 1
          env.parent[v] = u
          dfs(v, env)
          env.lowIndex[u] = min(env.lowIndex[v], env.lowIndex[u])
          if env.lowIndex[v] == env.start[v]:
            pass # found a bridge of two SCC(see tarjanSCC below)
        elif env.finish[v] == 0: # found a node opened, but not closed
          env.edge[u][v] = 2 # a back edge
          env.lowIndex[u] = min(env.lowIndex[v], env.lowIndex[u])
        elif env.start[v] > env.start[u]: # found a closed node that started later
          env.edge[u][v] = 3 # a down edge
        else:
          env.edge[u][v] = 4 # a cross edge
      env.index += 1
      env.finish[u] = env.index

    for u in xrange(self.n):
      if env.start[u] == 0: # an untouched node
        env.parent[u] = -1 # empty parent
        dfs(u, env)

  """
  Topological sort by removing node in-dergree = 0
  O(|V| + |E|)
  """
  def topologicalSort(self):
    order = []
    n = self.n
    # Count the incoming edges
    incomingDegree = [0] * n
    for x in xrange(n):
      for node in self.adjacents[x]:
        incomingDegree[node] += 1

    for x in xrange(n):
      if incomingDegree[x] == 0:
        order.append(x)
    # index that point to node that having proceed
    index = 0
    while index < len(order):
      currentNode = order[index]
      for nextNode in self.adjacents[currentNode]:
        incomingDegree[nextNode] -= 1
        if incomingDegree[nextNode] == 0:
          order.append(nextNode)
      index += 1

    if len(order) < n:
      raise IndexError('This graph is not a DAG')
    return order

  """
  Tarjan's Algorithm
  finding the strongly connected components of a graph.
  proceess with a DFS.
  O(|V| + |E|)
  """
  def tarjanSCC(self):
    class Env:
      def __init__(self, n):
        self.start = [0] * n
        self.closed = [0] * n
        self.lowIndex = [0] * n
        self.scc = []
        self.stack = []
        self.index = 0

    env = Env(self.n)

    def dfs(x, env):
      env.index += 1
      env.start[x] = env.index
      env.lowIndex[x] = env.index
      env.stack.append(x)
      for y in self.adjacents[x]:
        if env.start[y] == 0: #untouched
          dfs(y, env)
          env.lowIndex[x] = min(env.lowIndex[y], env.lowIndex[x])
        elif env.closed[y] == 0:
          env.lowIndex[x] = min(env.lowIndex[y], env.lowIndex[x])
      env.closed[x] = 1

      if env.lowIndex[x] == env.start[x]:
        # found a scc, pop the stack until the top one == x
        scc = []
        while env.stack[-1] != x:
          scc.append(env.stack.pop())
        scc.append(env.stack.pop())
        env.scc.append(scc)

    for x in xrange(self.n):
      if env.start[x] == 0:
        dfs(x, env)
    return env.scc

"""
For density grpah
"""

"""
Floyd-Warshall algorithm:
finding shortest paths in a weighted graph with positive or
negative edge weights (but with no negative cycles, see below) and
also for finding transitive closure of a relation R
O(n^3)
for every x, s->x && x->t => s->t
"""
def floydWarshallTransitive(array2D):
  for x in xrange(n):
    array2D[x][x] = True
    for s in xrange(n):
      if array2D[s][x]:
        for t in xrange(n):
          if array2D[x][t]:
            array2D[s][t] = True





class TestGraph(unittest.TestCase):
  def setUp(self):
    pass

  def testTopo(self):
    graph = Graph(4)
    graph.insertList(2, [1, 3])
    graph.insertList(1, [0])
    graph.insertList(3, [0, 1])
    self.assertEquals([2, 3, 1, 0], graph.topologicalSort())

  def testSCC(self):
    graph = Graph(9)
    graph.insertList(0, [1])
    graph.insertList(1, [2])
    graph.insertList(2, [0, 3])
    graph.insertList(3, [4, 6])
    graph.insertList(4, [5])
    graph.insertList(5, [3])
    graph.insertList(6, [7])
    graph.insertList(7, [8])
    graph.insertList(8, [6])
    self.assertEquals([[8, 7, 6], [5, 4, 3], [2, 1, 0]], graph.tarjanSCC())
    graph.generalDFS()

  def testAll(self):
    pass

if __name__ == '__main__':
  unittest.main()
