"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for DFS.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of DFS.
"""

import unittest

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

class MaxLoadingProblem:
  class MaxLoadingProblemCandidate:
    def __init__(self, selected, remainWeight):
      self.selected = selected
      self.currentWeight = 0
      self.pendingIndex = 0
      self.remainWeight = remainWeight

    def __repr__(self):
      return self.selected.__repr__()

  def __init__(self, weights, maxWeight):
    self.maxWeight = maxWeight
    self.weights = weights
    self.n = len(weights)
    self.bestWeight = 0
    self.bestSolution = None


  def getRoot(self):
    return self.MaxLoadingProblemCandidate([0] * self.n, sum(self.weights))

  def reject(self, candidate):
    return candidate.currentWeight > self.maxWeight

  def underBound(self, candidate):
    candidate.currentWeight + candidate.remainWeight < self.bestWeight

  def accept(self, candidate):
    return candidate.pendingIndex >= self.n

  def record(self, candidate):
    if candidate.currentWeight > self.bestWeight:
      self.bestWeight = candidate.currentWeight
      self.bestSolution = list(candidate.selected)

  def fristExtend(self, candidate):
    candidate.remainWeight -= self.weights[candidate.pendingIndex]
    candidate.pendingIndex += 1
    return candidate

  def nextExtent(self, candidate):
    if candidate.selected[candidate.pendingIndex - 1] == 0:
      candidate.selected[candidate.pendingIndex - 1] = 1
      candidate.currentWeight += self.weights[candidate.pendingIndex - 1]
      return candidate
    else:
      candidate.pendingIndex -= 1
      candidate.selected[candidate.pendingIndex] = 0
      candidate.currentWeight -= self.weights[candidate.pendingIndex]
      candidate.remainWeight += self.weights[candidate.pendingIndex]
      return None

class Test(unittest.TestCase):
  def setUp(self):
    pass

  def testMaxLoading(self):
    problem = MaxLoadingProblem([0,1,2,3,4,5], 11)
    backTracking(problem)
    self.assertEquals(11, problem.bestWeight)
    self.assertEquals([0,0,1,0,1,1], problem.bestSolution)


if __name__ == '__main__':
  unittest.main()
