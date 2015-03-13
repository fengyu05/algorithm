"""TODO(gnefihz): DO NOT SUBMIT without one-line documentation for search.

TODO(gnefihz): DO NOT SUBMIT without a detailed description of search.
"""

import unittest
from heapq import heappop, heappush

"""
Genernal Breath first search
"""
def BFS(startState, terminateState):
  if startState == terminateState:
    return 0, []
  opened = [startState]
  cost = {}
  cost[startState] = 0
  while len(opened) > 0:
    current = opened.pop(0)
    for nextState in current.getNexts():
      if nextState not in cost:
        cost[nextState] = cost[current] + 1
        nextState.fromState = current

        if nextState == terminateState:
          return cost[nextState], nextState.getPath()
        opened.append(nextState)
  return -1, []

"""
General a star search
"""
def AStar(startState, terminateState):
  if startState == terminateState:
    return 0, []
  opened = []
  heappush(opened, (0, startState))
  cost = {}
  cost[startState] = 0
  while len(opened) > 0:
    h, current = heappop(opened)
    #print current
    if current.g > cost[current]: # have visit with a low past cost
      continue
    for nextState in current.getNexts():
      g = cost[current] + 1
      if nextState not in cost or g < cost[nextState]:
        cost[nextState] = g
        nextState.g = g
        nextState.fromState = current

        if nextState == terminateState:
          return g, nextState.getPath()
        heappush(opened, (nextState.heuristicCostEstimate(), nextState))
  return -1, []

"""
General iterative depening depth first search
"""
def IDA(startState, terminateState, protectDeep=32):
  if startState == terminateState:
    return 0, []
  maxDeep = startState.heuristicEstimate()
  while maxDeep < protectDeep:
    cost = {}
    cost[startState] = 0
    opened = [startState]
    while len(opened) > 0:
      current = opened.pop()
      for nextState in current.getNexts():
        g = cost[current] + 1
        if (nextState not in cost or g < cost[nextState]) and \
          g + nextState.heuristicEstimate() <= maxDeep:
          cost[nextState] = g
          nextState.fromState = current
          if nextState == terminateState:
            return cost[nextState], nextState.getPath()
          opened.append(nextState)
    maxDeep += 1
  return -1, []


"""
State represent for eight digits.
"""
class State:
  def __init__(self, sequence):
    assert(len(sequence) == 9)
    self.sequence = sequence
    self.g = 0
    self.fromState = None

  def Hamilton(self, a, b):
    return abs(a/3 - b/3) + abs(a%3 - b%3)

  def heuristicEstimate(self):
    value = 0
    targetPosision = [8, 0, 1, 2, 3, 4, 5, 6, 7]
    for index, x in enumerate(self.sequence):
      value += self.Hamilton(index, targetPosision[x])
    return value

  def heuristicCostEstimate(self):
    return self.g + self.heuristicEstimate()

  def __eq__(self, other):
    return self.sequence == other.sequence

  def __hash__(self):
    hashValue = 0
    factor = 1
    for index in xrange(9):
      factor *= (index + 1)
      inverse = 0
      for j in range(index):
        if self.sequence[j] > self.sequence[index]:
          inverse += 1
      hashValue += factor * inverse
    return hashValue

  def __repr__(self):
    if not self.fromState is None:
      return "%d %d\n%s\n%s\n%s\n from\n%s\n%s\n%s\n" % (self.g, self.heuristicCostEstimate(),
          self.sequence[0:3], self.sequence[3:6], self.sequence[6:9],
          self.fromState.sequence[0:3], self.fromState.sequence[3:6], self.fromState.sequence[6:9])
    else:
      return "%d %d\n%s\n%s\n%s\n" % (self.g, self.heuristicCostEstimate(),
          self.sequence[0:3], self.sequence[3:6], self.sequence[6:9])

  def getNexts(self):
    nextStates = []
    switchPoints = [
      [1, 3],
      [0, 2, 4],
      [1, 5],
      [0, 4, 6],
      [1, 3, 5, 7],
      [2, 4, 8],
      [3, 7],
      [4, 6, 8],
      [5, 7]
      ]
    zeroPosition = self.sequence.index(0)
    for switchPoint in switchPoints[zeroPosition]:
      newSequence = list(self.sequence)
      newSequence[zeroPosition], newSequence[switchPoint] = newSequence[switchPoint], newSequence[zeroPosition]
      nextStates.append(State(newSequence))
    return nextStates

  def getPath(self):
    current = self
    path = []
    step = 0
    while not current is None:
      step += 1
      assert(step < 65536)
      path.append(current)
      current = current.fromState
    return path


"""
A* search on 8-dights problem
f = g(past step) + heuristic(Hamilton distance)
"""
def EightDigits_AStar(startSequence):
  startState = State(startSequence)
  terminateState = State([1,2,3,4,5,6,7,8,0])
  return AStar(startState, terminateState)

def EightDigits_BFS(startSequence):
  startState = State(startSequence)
  terminateState = State([1,2,3,4,5,6,7,8,0])
  return BFS(startState, terminateState)

def EightDigits_IDA(startSequence):
  startState = State(startSequence)
  terminateState = State([1,2,3,4,5,6,7,8,0])
  return IDA(startState, terminateState)

class Test(unittest.TestCase):
  def setUp(self):
    pass

  def testBFS(self):
    self.assertEquals(0, EightDigits_BFS([1,2,3,4,5,6,7,8,0])[0])
    self.assertEquals(1, EightDigits_BFS([1,2,3,4,5,6,7,0,8])[0])
    self.assertEquals(4, EightDigits_BFS([1,5,2,4,0,3,7,8,6])[0])

  def testAStar(self):
    self.assertEquals(0, EightDigits_AStar([1,2,3,4,5,6,7,8,0])[0])
    self.assertEquals(1, EightDigits_AStar([1,2,3,4,5,6,7,0,8])[0])
    (step, path) = EightDigits_AStar([1,5,2,4,0,3,7,8,6])
    self.assertEquals(4, step)
    (step, path) = EightDigits_AStar([8,7,4,0,5,1,6,3,2])
    self.assertEquals(21, step)
    self.assertEquals(path, EightDigits_BFS([8,7,4,0,5,1,6,3,2])[1])

  def testIDA(self):
    self.assertEquals(0, EightDigits_IDA([1,2,3,4,5,6,7,8,0])[0])
    self.assertEquals(1, EightDigits_IDA([1,2,3,4,5,6,7,0,8])[0])
    (step, path) = EightDigits_IDA([1,5,2,4,0,3,7,8,6])
    self.assertEquals(4, step)
    (step, path) = EightDigits_IDA([8,7,4,0,5,1,6,3,2])
    self.assertEquals(21, step)
    self.assertEquals(path, EightDigits_AStar([8,7,4,0,5,1,6,3,2])[1])

if __name__ == '__main__':
  unittest.main()

