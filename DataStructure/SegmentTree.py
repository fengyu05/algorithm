"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for data_structure.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of data_structure.
"""

import unittest

"""
General Segment Tree for interval statistics.
"""
class SegmentTreeNode:
  def __init__(self, begin, end):
    self.begin = begin
    self.end = end
    self.count = 0
    self.left = None
    self.right = None
    self.m = 0
    self.leftBound = 0
    self.rightBound = 0
    self.line = 0

  def isLeaf(self):
    return self.end - self.begin == 1

  def middle(self):
    return (self.begin + self.end) / 2

class SegmentTree:
  """
  Create a new interval [begin, end)
  """
  def __init__(self, begin, end):
    self.root = self.build(begin, end)

  def build(self, begin, end):
    parent = SegmentTreeNode(begin, end)
    if end - begin > 1:
      middle = (begin + end) / 2
      parent.left = self.build(begin, middle)
      parent.right = self.build(middle, end)
    return parent

  """
  [x, y) += value
  """
  def update(self, x, y, value=1, node=None):
    if node == None:
      node = self.root
    # node in [x, y)
    if x <= node.begin and node.end <= y:
      node.count += value
    elif not node.isLeaf():
      middle = (node.begin + node.end) / 2
      if x < middle:
        self.update(x, y, value, node.left)
      if middle < y:
        self.update(x, y, value, node.right)
    self.updateM(node)
    self.updateLines(node)

  """
  How many points is cover in the interval
  """
  def updateM(self, node):
    if node.count > 0:
      node.m = node.end - node.begin
    elif node.isLeaf():
      node.m = 0
    else:
      node.m = node.left.m + node.right.m

  """
  Number of lines in the interval
  """
  def updateLines(self, node):
    if node.count > 0:
      node.leftBound = node.rightBound = node.line = 1
    elif node.isLeaf():
      node.leftBound = node.rightBound = 0
    else:
      node.leftBound = node.left.leftBound
      node.rightBound = node.right.rightBound
      node.line = node.left.line + node.right.line - (node.left.rightBound * node.right.leftBound)


  def query(self, point, node=None):
    if node == None:
      node = self.root
    if point < node.begin or point >= node.end:
      return 0
    value = node.count
    if node.isLeaf():
      return node.count
    middle = node.middle()
    if point < middle:
      value += self.query(point, node.left)
    elif point >= middle:
      value += self.query(point, node.right)
    return value


class Test(unittest.TestCase):
  def setUp(self):
    pass

  def testSegmentTree(self):
    segmentTree = SegmentTree(0, 10)
    segmentTree.update(2, 7)
    self.assertEquals(5, segmentTree.root.m)
    segmentTree.update(3, 5)
    self.assertEquals(1, segmentTree.root.line)
    segmentTree.update(4, 7)
    segmentTree.update(0, 10)
    segmentTree.update(6, 9)

    self.assertEquals(1, segmentTree.query(0))
    self.assertEquals(1, segmentTree.query(1))
    self.assertEquals(2, segmentTree.query(2))
    self.assertEquals(3, segmentTree.query(3))
    self.assertEquals(4, segmentTree.query(4))
    self.assertEquals(3, segmentTree.query(5))
    self.assertEquals(4, segmentTree.query(6))
    self.assertEquals(2, segmentTree.query(7))
    self.assertEquals(2, segmentTree.query(8))
    self.assertEquals(1, segmentTree.query(9))
    self.assertEquals(0, segmentTree.query(10))


if __name__ == '__main__':
  unittest.main()
