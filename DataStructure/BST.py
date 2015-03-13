"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for BST.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of BST.
"""
import unittest


"""
Binary search tree without using recursion
"""
class BST:
  class Node:
    def __init__(self, key, parent=None, left=None, right=None):
      self.key = key
      self.left = left
      self.right = right
      self.parent = parent

  def __init__(self):
    self.root = None

  def insert(self, key):
    node = self.root
    if node is None:
      self.root = self.Node(key)
      return
    while node and node.left and key < node.key:
      node = node.left
    while node and node.right and key > node.key:
      node = node.right

    newNode = self.Node(key, node)
    if key < node.key:
      node.left = newNode
    elif key > node.key:
      node.right = newNode
    else: #a duplicated root
      pass

  def remove(self, key):
    node = self.search(key)
    if node is None:
      return False

    # perform a remove at a incompleted node
    if not (node.left and node.right):
      inCompletedNode = node
    else:
      # find a incompleted node to replace the current node
      inCompletedNode = self.successor(node)
      node.key = inCompletedNode.key

    # find the single child of the incompleted node
    if inCompletedNode.left:
      singleChildNode = inCompletedNode.left
    else:
      singleChildNode = inCompletedNode.right

    # link the single child to incompleted node's parent
    if singleChildNode:
      singleChildNode.parent = inCompletedNode.parent
    if inCompletedNode.parent is None:
      self.root = singleChildNode
    elif inCompletedNode == inCompletedNode.parent.left:
      inCompletedNode.parent.left = singleChildNode
    else:
      inCompletedNode.parent.right = singleChildNode
    return True

  def _walk(self,
            preOrderFunc=None, inOrderFunc=None, postOrderFunc=None, node=None):
    if node is None:
      node = self.root
    preOrderFunc and preOrderFunc(node)
    if node.left:
      self._walk(preOrderFunc, inOrderFunc, postOrderFunc, node.left)
    inOrderFunc and inOrderFunc(node)
    if node.right:
      self._walk(preOrderFunc, inOrderFunc, postOrderFunc, node.right)
    postOrderFunc and postOrderFunc(node)


  def search(self, key, node=None):
    if node is None:
      node = self.root
    if node.key == key:
      return node
    if node.left and key < node.key:
      return self.search(key, node.left)
    elif node.right and key > node.key:
      return self.search(key, node.right)
    return None

  def min(self, node=None):
    if node is None:
      node = self.root
    while node and (not node.left is None):
      node = node.left
    return node

  def max(self):
    node = self.root
    while node and (not node.right is None):
      node = node.right
    return node

  def successor(self, node):
    if node.right:
      return self.min(node.right)
    parentNode = node.parent
    while parentNode and parentNode.right == node:
      node = parentNode
      parentNode = parentNode.parent
    return parentNode

  def predecsessor(self, node):
    if node.left:
      return self.max(node.left)
    parentNode = node.parent
    while parentNode and parentNode.left == node:
      node = parentNode
      parentNode = parentNode.parent
    return parentNode

class Test(unittest.TestCase):
  def setUp(self):
    pass

  def testBST(self):
    bst = BST()
    """
    5 -> 8  -> 10
               -> 9
         -> 7

    -> 1 -> 4
            -> 3
       -> 0

    pre:5 1 0 4 3 8 7 10 9
    in:0 1 3 4 5 7 8 9 10
    post:0 3 4 1 7 9 10 8 5
    """
    bst.insert(5)
    bst.insert(8)
    bst.insert(10)
    bst.insert(9)
    bst.insert(7)
    bst.insert(1)
    bst.insert(0)
    bst.insert(4)
    bst.insert(3)

    class Recorder:
      def __init__(self):
        self.path = []
      def __call__(self, node):
        self.path.append(node.key)

    preFunc = Recorder()
    inFunc = Recorder()
    postFunc = Recorder()
    bst._walk(preFunc, inFunc, postFunc)
    self.assertEquals([5,1,0,4,3,8,7,10,9], preFunc.path)
    self.assertEquals([0,1,3,4,5,7,8,9, 10], inFunc.path)
    self.assertEquals([0,3,4,1,7,9,10,8,5], postFunc.path)

    self.assertEquals(0, bst.min().key)
    self.assertEquals(10, bst.max().key)
    self.assertEquals(None, bst.search(11))
    self.assertEquals(8, bst.successor(bst.search(7)).key)
    """
    After remove
    5 -> 9 -> 10
        -> 7
    -> 1 -> 3
       -> 0
    """
    bst.remove(8)
    bst.remove(4)
    preFunc = Recorder()
    inFunc = Recorder()
    postFunc = Recorder()
    bst._walk(preFunc, inFunc, postFunc)
    self.assertEquals([5,1,0,3,9,7,10], preFunc.path)
    self.assertEquals([0,1,3,5,7,9,10], inFunc.path)
    self.assertEquals([0,3,1,7,10,9,5], postFunc.path)

if __name__ == '__main__':
  unittest.main()
