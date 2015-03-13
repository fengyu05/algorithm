"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for shortest_path.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of shortest_path.
"""

import unittest
from heapq import heappush, heappop

"""
Dijkstra algorithm using a binary heap
O(nlogn)
"""
def dijkstraShortestPath(array2D, source):
  n = len(array2D)
  assert (len(array2D[0]) == n)
  distances = [float('Inf')] * n
  distances[source] = 0
  opened = []
  heappush(opened, (0, source))
  while len(opened) > 0:
    (currectDistance, vertex) = heappop(opened)
    if currectDistance != distances[vertex]: #have been updated
      continue
    for x in xrange(n):
      if x != vertex and distances[x] > distances[vertex] + array2D[vertex][x]:
        distances[x] = distances[vertex] + array2D[vertex][x]
        heappush(opened, (distances[x], x))
  return distances

"""
Floyd algorihm
O(n^3)
"""
def floydShortestPath(array2D):
  distances = array2D[:]
  n = len(array2D)
  for x in xrange(n):
    for i in xrange(n):
      for j in xrange(n):
        if distances[i][j] > distances[i][x] + distances[x][j]:
          distances[i][j] = distances[i][x] + distances[x][j]
  for x in xrange(n):
    if distances[x][x] < 0:
      return False
  return True, distances


"""
Bellman algorithm for negative edge
O(nm)
"""
def Bellman(array2D):
  pass

class Test(unittest.TestCase):
  def setUp(self):
    inf = float('Inf')

    array2D = [[inf] * 5 for x in xrange(5)]
    for x in xrange(5):
      array2D[x][x] = 0
    array2D[0][1] = array2D[1][0] = 1
    array2D[0][3] = array2D[3][0] = 3
    array2D[0][4] = array2D[4][0] = 1

    array2D[1][2] = array2D[2][1] = 2
    array2D[1][4] = array2D[4][1] = 4

    array2D[2][3] = array2D[3][2] = 2
    array2D[2][4] = array2D[4][2] = 3

    array2D[3][4] = array2D[4][3] = 5

    self.array2D = array2D

  def testDijkstra(self):

    distances = dijkstraShortestPath(self.array2D, 0)
    self.assertEquals([0, 1, 3, 3, 1], distances)

  def testFloyd(self):
    distances = floydShortestPath(self.array2D)[1]
    self.assertEquals([0, 1, 3, 3, 1], distances[0])



if __name__ == '__main__':
  unittest.main()
