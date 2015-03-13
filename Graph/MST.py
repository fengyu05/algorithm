"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for MST.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of MST.
"""

import unittest
import heapq

"""
For sparse graph
"""
class WeightGraph:
  """
  Create a graph with n node [0, n)
  """
  def __init__(self, n):
    self.n = n
    self.adjacents = {}

  """
  Insert a edit x->y
  """
  def insert(self, x, y, w):
    if x not in self.adjacents:
      self.adjacents[x] = {}
    self.adjacents[x][y] = w

  def insertList(self, x, nodeList):
    for (y, w) in nodeList:
      self.insert(x, y, w)

  def remove(self, x, y):
    del self.adjacents[x][y]

  def hasEdge(self, x, y):
    y in self.adjacents[x]

  """
  Prim's algorithm 
  O(|E| log |V|)
  """
  def primMST(self):

    totalWeight = 0
    closed = [0] * self.n
    nodeHeap = []
    heapq.heappush(nodeHeap, (0, 0)) # start from 0 node
    totalNodeCount = 0
    while len(nodeHeap) > 0:
      (w, node) = heapq.heappop(nodeHeap)
      if closed[node] == 0:
        closed[node] = 1
        totalWeight += w
        totalNodeCount += 1
        if totalNodeCount == self.n:
          break
        for nextNode, nextW in self.adjacents[node].iteritems():
          if closed[nextNode] == 0:
            heapq.heappush(nodeHeap, (nextW, nextNode))

    return totalWeight

class Edge:
  def __init__(self, x, y, w):
    self.x = x
    self.y = y
    self.w = w

  def __repr__(self):
    return '(%d->%d:%d)' % (self.x, self.y, self.w)

  def compareKey(self):
    return self.w

"""
A disjion set without union by rank
"""
class DisjoinSet:
  def __init__(self, n):
    self.n = n
    self.parent = {}
    self.rank = {}

  """
  Apply path compression
  """
  def find(self, x):
    if x not in self.parent:
      return x
    else:
      self.parent[x] = self.find(self.parent[x])
      return self.parent[x]

  """
  Union by rank
  """
  def union(self, x, y):
    rootX = self.find(x)
    rootY = self.find(y)

    if rootX == rootY:
      return

    rankX = self.rank.get(x, 0)
    rankY = self.rank.get(y, 0)

    if rankX < rankY:
      self.parent[rootX] = rootY
    elif rankY < rankX:
      self.parent[rootY] = rootX
    else:
      self.rank[rootY] = rankY + 1
      self.parent[rootX] = rootY

"""
Kruskal on a edge list
O(E * log(E))
"""
def kruskalMst(edgeList, n):
  totalWeight = 0
  edgeList.sort(key=Edge.compareKey)
  treeEdgeList = []
  disjionSet = DisjoinSet(n)

  for edge in edgeList:
    rootX = disjionSet.find(edge.x)
    rootY = disjionSet.find(edge.y)
    if rootX != rootY:
      disjionSet.union(edge.x, edge.y)
      totalWeight += edge.w
      treeEdgeList.append(edge)
      if len(treeEdgeList) == n - 1:
        break
  return totalWeight, treeEdgeList


class TestGraph(unittest.TestCase):
  def setUp(self):
    pass

  def testMST(self):
    self.assertEquals(11,
        kruskalMst(
        [Edge(0, 1, 3), Edge(0, 2, 1), Edge(1, 2, 4),
         Edge(1, 3, 5), Edge(2, 3, 6), Edge(3, 4, 2),
         Edge(2, 4, 7)], 5)[0])

    graph = WeightGraph(5)
    graph.insert(0, 1, 3)
    graph.insert(0, 2, 1)
    graph.insert(1, 2, 4)
    graph.insert(1, 3, 5)
    graph.insert(2, 3, 6)
    graph.insert(3, 4, 2)
    graph.insert(2, 4, 7)

    self.assertEquals(11, graph.primMST())

if __name__ == '__main__':
  unittest.main()
