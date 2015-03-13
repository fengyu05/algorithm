"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for knapsack.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of knapsack.
"""
import unittest


"""
A dynamic programing to solve 0/1 knapsack problem
dp[itemIndex][capability] =
  if itemIndex == n:
      values[itemIndex] | 0 (capability > weights[itemIndex] ?)
  else:
  max( dp[itemIndex + 1][capability],
    dp[itemIndex + 1][capability - weights[itemIndex]] + values[itemIndex] | 0
    (capability > weight[itemIndex] ?)
    )
"""
def knapsackDp(weights, values, capability):
  n = len(weights)
  assert(len(weights) == len(values))
  dpArray2D = [ [0 for x in xrange(capability + 1)] for y in xrange(n)]

  #dp[n-1][weights[n-1]..capability] = values[n-1]
  index = n - 1
  if weights[index] <= capability:
    dpArray2D[index][weights[index]:] = \
    [values[index]] * (capability + 1 - weights[index])

  for index in xrange(n - 2, -1, -1):
    dpArray2D[index][:weights[index]] = dpArray2D[index + 1][:weights[index]]
    for x in xrange(weights[index], capability + 1):
      dpArray2D[index][x] = max(dpArray2D[index + 1][x],
                                dpArray2D[index + 1][x - weights[index]] + values[index])
  solution = [0] * n
  totalValue = dpArray2D[0][capability]
  for x in xrange(n - 1):
    if dpArray2D[x][capability] == dpArray2D[x + 1][capability]:
      solution[x] = 0
    else:
      solution[x] = 1
      capability -= weights[x]
  solution[n - 1] = dpArray2D[n - 1][capability] > 0 and 1 or 0

  return totalValue, solution

"""
A general back tracking search
"""
def backTracking(problem, candidate=None):
  if candidate is None:
    candidate = problem.getRoot()
  if problem.accept(candidate):
    problem.record(candidate)
    return
  extendCandidate = problem.fristExtend(candidate)
  while not extendCandidate is None:
    if not (problem.reject(extendCandidate) or
            problem.underBound(extendCandidate)):
      backTracking(problem, extendCandidate)
    extendCandidate = problem.nextExtent(extendCandidate)

"""
Knapsack problem using backtracking
"""
class KnapsackProblem:
  class KnapsackProblemCandidate:
    def __init__(self, selected, remainValue):
      self.selected = selected
      self.currentWeight = 0
      self.currentValue = 0
      self.pendingIndex = 0
      self.remainValue = remainValue

    def __repr__(self):
      return self.selected.__repr__()

  class Item:
    def __init__(self, weight, value):
      self.weight = weight
      self.value = value

    def __cmp__(self, other):
      valueSelf = self.value // self.weight
      valueOther = other.value // other.weight
      if valueSelf < valueOther:
        return -1
      else:
        return 1


  def __init__(self, weights, values, capability):
    self.weights = weights
    self.values = values
    self.n = len(weights)
    items = []
    for x in xrange(self.n):
      item = self.Item(weights[x], values[x])
      items.append(item)
    self.items = sorted(items)
    self.capability = capability
    self.bestValue = 0
    self.bestSolution = None


  def getRoot(self):
    return self.KnapsackProblemCandidate([0] * self.n, sum(self.values))

  def reject(self, candidate):
    return candidate.currentWeight > self.capability

  def underBound(self, candidate):
    candidate.currentValue + candidate.remainValue < self.bestValue

  def accept(self, candidate):
    return candidate.pendingIndex >= self.n

  def record(self, candidate):
    if candidate.currentValue > self.bestValue:
      self.bestValue = candidate.currentValue
      self.bestSolution = list(candidate.selected)

  def fristExtend(self, candidate):
    candidate.remainValue -= self.values[candidate.pendingIndex]
    candidate.pendingIndex += 1
    return candidate

  def nextExtent(self, candidate):
    if candidate.selected[candidate.pendingIndex - 1] == 0:
      candidate.selected[candidate.pendingIndex - 1] = 1
      candidate.currentWeight += self.weights[candidate.pendingIndex - 1]
      candidate.currentValue += self.values[candidate.pendingIndex - 1]
      return candidate
    else:
      candidate.pendingIndex -= 1
      candidate.selected[candidate.pendingIndex] = 0
      candidate.currentWeight -= self.weights[candidate.pendingIndex]
      candidate.currentValue -= self.values[candidate.pendingIndex]
      candidate.remainValue += self.values[candidate.pendingIndex]
      return None

class Test(unittest.TestCase):
  def setUp(self):
    pass

  def testKnapsackDp(self):
    self.assertEquals(27, knapsackDp([1,2,1,3,2], [7,8,6,5,6], 6)[0]);
    self.assertEquals([1,1,1,0,1], knapsackDp([1,2,1,3,2], [7,8,6,5,6], 6)[1]);
    self.assertEquals(21, knapsackDp([1,2,1,3,2], [7,8,6,5,6], 5)[0]);
    self.assertEquals(21, knapsackDp([1,2,1,3,2], [7,8,6,5,6], 4)[0]);
    self.assertEquals(15, knapsackDp([1,2,1,3,2], [7,8,6,5,6], 3)[0]);
    self.assertEquals(13, knapsackDp([1,2,1,3,2], [7,8,6,5,6], 2)[0]);
    self.assertEquals(7, knapsackDp([1,2,1,3,2], [7,8,6,5,6], 1)[0]);
    self.assertEquals(0, knapsackDp([1,2,1,3,2], [7,8,6,5,6], 0)[0]);

    problem = KnapsackProblem([1,2,1,3,2], [7,8,6,5,6], 6)
    backTracking(problem)
    self.assertEquals(27, problem.bestValue)
    self.assertEquals([1,1,1,0,1], problem.bestSolution)



if __name__ == '__main__':
  unittest.main()
