"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for data_structure.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of data_structure.
"""

import unittest

class UnionFindSet:
  def __init__(self, n):
    self.n = self.n
    self.parent = [x for x in xrnage(n)]
    self.rank = [0] * n
    self.size = [1] * n

  def find(self, x):
    rootX = x
    while rootX != self.parent[rootX]:
      rootX = self.parent[rootX]
    while x != self.parent[x]:
      nextX = self.parent[x]
      self.parent[x] = rootX
      x = nextX
    return rootX

  def union(self, x, y):
    x = self.find(x)
    y = self.find(y)

    if self.rank[x] > self.rank[y]:
      self.parent[y] = x
      self.size[x] += self.size[y]
    else:
      self.parent[x] = y
      self.size[y] += self.size[x]

    if self.rank[x] == self.rank[y]:
      self.rank[y] += 1

  def size(self, x):
    return self.size[self.parent[x]]

class TrieNode:
  def __init__(self, char):
    self.char = char
    self.children = {}
    self.isLeaf = False

class Trie:
  def __init__(self):
    self.root = TrieNode('')

  """
  Insert a word into Trie, return True is new word inserted.
  """
  def insert(self, word):
    node = self.root
    for index, char in enumerate(word):
      if char not in node.children:
        node.children[char] = TrieNode(char)
      node = node.children[char]

    if node.isLeaf:
      return False
    else:
      node.isLeaf = True
      return True

"""
A degenerate segment tree like structure that use for count point in a interval
"""
class TreeArray:
  """
  Init a tree arary for interval [0, n)
  """
  def __init__(self, n):
    self.n = n
    self.array = [0] * self.n * 2 #allocate twice space

  """
  The lowest '1' bit of x in binary base
  """
  def lowBit(self, x):
    return x & (x ^ (x - 1))

  """
  Insert points (count = value) at x.
  """
  def add(self, x, value):
    while x <= self.n:
      self.array[x] += value
      x += self.lowBit(x)

  """
  Return the totals numer of points in [0, x]
  """
  def sum(self, x):
    result = 0
    while x > 0:
      result += self.array[x]
      x -= self.lowBit(x)
    return result



class Test(unittest.TestCase):
  def setUp(self):
    pass

  def testTrie(self):
    trie = Trie()
    self.assertEquals(True, trie.insert('gnefihz'))
    self.assertEquals(True, trie.insert('gnefih'))
    self.assertEquals(True, trie.insert('fengyu'))
    self.assertEquals(True, trie.insert('feng'))
    self.assertEquals(True, trie.insert('xxx'))
    self.assertEquals(False, trie.insert('feng'))
    self.assertEquals(False, trie.insert('gnefihz'))
    self.assertEquals(False, trie.insert('xxx'))

  def testTreeArray(self):
    treeArray = TreeArray(100)
    treeArray.add(3, 10)
    treeArray.add(100, 10)
    treeArray.add(34, 10)
    treeArray.add(64, 10)
    treeArray.add(1, 10)
    self.assertEquals(10 * 3, treeArray.sum(50))
    self.assertEquals(10 * 5, treeArray.sum(100))


if __name__ == '__main__':
  unittest.main()
