"""
Common function use in combinatics
"""

import unittest
import math

def P(n, k):
  result = 1
  for i in xrange(n - k + 1, n + 1):
    result = result * i;
  return result

def C(n, k):
  if k < 0:
    return 0
  if k == 0:
    return 1
  result = 1
  if k > n - k:
    k = n - k
  for i  in xrange(n - k + 1, n + 1):
    result = result * i / (i - (n - k))
  return result

"""
c[i][j] = c[i-1][j] + cpi-1][j-1]
"""
def CombinationWithDp(n):
  array2D = [[0 for _ in xrange(0, x + 1)] for x in xrange(n + 1)]
  array2D[0][0] = 1;
  for i in xrange(1, n + 1):
    array2D[i][0] = 1;
    array2D[i][i] = 1;
    for j in range(1, i):
      array2D[i][j] = array2D[i - 1][j] + array2D[i - 1][j - 1];
  return array2D

"""
Stirling's approximation (or Stirling's formula) is an approximation for factorials. 
ln(n!) = n*ln(n) - n + O(ln(n))
=>
n! = sqrt(2*pi*n) (n/e)^n
"""
def StirlingApproximation(n):
  return math.sqrt(2 * math.pi * n) * (n / math.e)**n

class TestCombination(unittest.TestCase):
  def setUp(self):
    pass

  def testAll(self):
    self.assertEquals(P(10, 3), 10 * 9 * 8)
    self.assertEquals(C(10, 3), 10 * 9 * 8 / (1 * 2 * 3))
    self.assertEquals(CombinationWithDp(10)[10][5], C(10, 5))
    self.assertTrue(abs(StirlingApproximation(10) - P(10, 10)) <
                      P(10, 10) / 10)

if __name__ == '__main__':
  unittest.main()
