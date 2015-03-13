"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for kth.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of kth.
"""
import unittest

def swap(array, x, y):
  array[x], array[y] = array[y], array[x]

def partition(array, start, end):
  I = start + 1
  J = I
  pivot = start
  while I < end:
    if array[I] < array[pivot]:
      swap(array, I, J)
      J += 1
    I += 1
  swap(array, pivot, J - 1)
  return J-1

def _findKth(array, start, end, kth):
  if start < end:
    partitionIndex = partition(array, start, end)

    if partitionIndex == kth - 1:
      return array[partitionIndex]
    elif partitionIndex > kth - 1:
      return _findKth(array, start, partitionIndex, kth)
    else:
      return _findKth(array, partitionIndex + 1, end, kth)

def findKth(array, kth):
  return _findKth(array, 0, len(array), kth)


class test(unittest.TestCase):

  def test(self):
    self.assertEquals(1, findKth([4,2,1,7,5,3,8,10,9,6], 1))
    self.assertEquals(2, findKth([4,2,1,7,5,3,8,10,9,6], 2))
    self.assertEquals(3, findKth([4,2,1,7,5,3,8,10,9,6], 3))
    self.assertEquals(4, findKth([4,2,1,7,5,3,8,10,9,6], 4))
    self.assertEquals(5, findKth([4,2,1,7,5,3,8,10,9,6], 5))
    self.assertEquals(6, findKth([4,2,1,7,5,3,8,10,9,6], 6))
    self.assertEquals(7, findKth([4,2,1,7,5,3,8,10,9,6], 7))
    self.assertEquals(8, findKth([4,2,1,7,5,3,8,10,9,6], 8))
    self.assertEquals(9, findKth([4,2,1,7,5,3,8,10,9,6], 9))
    self.assertEquals(10, findKth([4,2,1,7,5,3,8,10,9,6], 10))


if __name__ == '__main__':
  unittest.main()
