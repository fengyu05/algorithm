
class Solution {

  class State implements Iterable<State> {

    @Override
    public Iterator<State> iterator() {
        Iterator<State> it = new Iterator<State>() {
            @Override
            public boolean hasNext() {
            }

            @Override
            public Type next() {
            }

            @Override
            public void remove() {
            }
        };
        return it;
    }
  }

  int BFS(State s, State t) {
    Queue<State> open = new Deque<>();
    Map<State, Integer> close = new HashMap<>();

    open.add(s);
    close.put(s, 0);
    while (open.size() > 0) {
      State cur = open.poll();
      if (cur.equals(t)) return close.get(cur);
      for (State next : cur.getNext()) {
        if (!close.containsKey(next)) {
          close.put(next, close.get(cur) + 1);
          open.add(next);
        }
      }
    }
  }
}
