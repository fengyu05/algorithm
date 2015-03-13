"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for HuffmanCode.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of HuffmanCode.
"""

import unittest
from heapq import *

class HuffmanCodeNode:
  def __init__(self, code, weight):
    self.code = code
    self.weight = weight
    self.leftChild = None
    self.rightChild = None

  def __cmp__(self, other):
    return self.weight - other.weight

def CreateHuffmanTree(codes, weights):
  nodeCount = len(codes)
  assert(nodeCount == len(weights))
  assert(nodeCount > 1)
  heap = []
  for idx, code in enumerate(codes):
    heappush(heap, HuffmanCodeNode(code, weights[idx]))
  while len(heap) > 1:
    node1 = heappop(heap)
    node2 = heappop(heap)
    inNode = HuffmanCodeNode(None, node1.weight + node2.weight)

    inNode.leftChild = node1
    inNode.rightChild = node2
    heappush(heap, inNode)

  return heappop(heap)

def listCode(rootNode, code=""):
  if not rootNode.leftChild and not rootNode.rightChild:
    print(rootNode.code, code)
  if rootNode.leftChild:
    listCode(rootNode.leftChild, code + '0')
  if rootNode.rightChild:
    listCode(rootNode.rightChild, code + '1')

def decode(currentNode, code):
  for char in code:
    if char == '0' and currentNode.leftChild:
      currentNode = currentNode.leftChild
    elif char == '1' and currentNode.rightChild:
      currentNode = currentNode.rightChild
    else:
      return None
  return currentNode.code


class Test(unittest.TestCase):
  def setUp(self):
    pass

  def testHuffmanCode(self):
    rootNode = CreateHuffmanTree(
        ['b','p','`','m','o','d','j','a','i','r','u','l','s','e',' '],
        [1,1,2,2,3,3,3,4,4,5,5,6,6,8,12])
    listCode(rootNode)
    self.assertEquals('l', decode(rootNode, '1111'))
    self.assertEquals('b', decode(rootNode, '100010'))

if __name__ == '__main__':
  unittest.main()
