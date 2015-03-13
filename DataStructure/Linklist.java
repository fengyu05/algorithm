
/**
 * Common manipulation on linkist.
 */

/**
  * ListLink Node
  */
class ListNode {
  int val;
  ListNode next;
  ListNode(int x) {
    val = x;
    next = null;
  }
}

class Solution {

    private void swap(ListNode a, ListNode b) {
        if (a == b) return;
        int tmp = a.val; a.val = b.val; b.val = tmp;
    }

    /**
     * A recursion for quick sort on a linklist.
     */
    private void _quickSort(ListNode head, ListNode end) {
        if (head == end || head.next == null) return; // size == 1
        if (head.next == end) { // size == 2
            if (head.val > head.next.val) {
                swap(head, head.next);
            }
            return;
        }
        
        ListNode pivot = head; // pivot node
        ListNode nextSlot = head.next; // next unsort node 
        ListNode sortedSlot = null; // sorted node
        for (ListNode curr = head.next; curr != end; curr = curr.next) {
            if (curr.val < pivot.val) {
                swap(curr, nextSlot);
                sortedSlot = nextSlot;
                nextSlot = nextSlot.next;  
            }
        }
        if (sortedSlot != null) { // at least have one node less than pivot
            swap(pivot, sortedSlot);
            _quickSort(head, sortedSlot);
        }
        if (nextSlot != null) { // at least have one node bigger than pivot
            _quickSort(nextSlot, end);
        }
    }
    
    /**
     * Quick Sort a linklist.
     */
    public ListNode quickSort(ListNode head) {
        if (head == null) return null;
        if (head.next == null) return head;
        _quickSort(head, null);
        return head;
    }

    /**
     * Merge two sorted link list.
     * Using a guard node to make coding easy.
     */
    public ListNode mergeList(ListNode a, ListNode b) {
      ListNode head = new ListNode(-1); //guard
      ListNode curr = head;
      while(a != null && b != null) {
        if (a.val < b.val) {
          curr.next = a;
          a = a.next;
        } else {
          curr.next = b;
          b = b.next;
        }
        curr = curr.next;
      }
      curr.next = a != null ? a : b;
      return head.next;
    }

    /**
     * Merge sort on link list.
     */
    public ListNode mergeSort(ListNode head) {
        if (head == null) return null;
        if (head.next == null) return head;
        ListNode mid = head, curr = head;
        while (curr.next != null && curr.next.next != null) { // find the mid;
            mid = mid.next;
            curr = curr.next.next;
        }
        ListNode midNext = mid.next;
        mid.next = null;
        return mergeList(sortList(head), sortList(midNext));
    }

    /**
      * Insertion sort.
      * using a guard for coding convenient.
      */
    public ListNode insertionSortList(ListNode head) {
        if (head == null) return null;
        if (head.next == null) return head;
        
        ListNode guard = new ListNode(Integer.MIN_VALUE);
        
        for (ListNode curr = head, next = null; curr != null; curr = next) {
            next = curr.next; // tmp next
            curr.next = null; // cut

            for(ListNode biggerNode = guard.next, prev = guard;
                prev != null; // till slot reach end
                prev = biggerNode, biggerNode = biggerNode.next) {
                if (biggerNode == null || biggerNode.val > curr.val) { // find the slot to put curr
                    prev.next = curr;
                    curr.next = biggerNode;
                    break;
                }
            }
        }
        return guard.next;
    }

    /**
      * Detect whether a link list have cycle, and return the node that
      * the cycle begins.
      */
    public ListNode detectCycle(ListNode head) {
        if (head == null) return null;
        ListNode p1 = head, p2 = head;
        boolean found = false;
        while(p2.next != null && p2.next.next != null) {
            p1 = p1.next;
            p2 = p2.next.next;
            if (p1 == p2) {
                found = true;
                break;
            }
        }
        if (!found) return null; // link list end
        
        // from here we have found the cycle
        // p1: a -> X -> b  (X is the point cycle begin, a/b/c is a path)
        // p2: a -> X -> b -> c -> X
        // 2(a+b) = a + 2b + c => a = c
        // length of cycle L = b + c = a + b
        // now lookup the X point
        p1 = head;
        while (p1 != p2) {
            p1 = p1.next;
            p2 = p2.next;
        }
        return p1;
    }

    /**
      * Rotate link list to right for n nodes
      */
    public ListNode rotateRight(ListNode head, int n) {
        if (head == null) return null;

        int size = 1; // calculate size
        ListNode curr = head;
        while (curr.next != null) {size++; curr = curr.next;}
        ListNode tail = curr;

        // reduce n  
        if (n%size == 0) return head;
        n = n % size;
        int cut = size - n;

        // relink
        curr = head;
        ListNode prev = null;
        while (cut-- > 0) { prev = curr; curr = curr.next;}
        prev.next = null;
        tail.next = head;
        
        return curr;
    }


    /**
      * Merge k link lists with a heap
      */
    public ListNode mergeKLists(ArrayList<ListNode> lists) {
        PriorityQueue<ListNode> heap = new PriorityQueue<>(100, new Comparator<ListNode>() {
           @Override
           public int compare(ListNode a, ListNode b) { return a.val - b.val; }
        });
        ListNode guard = new ListNode(Integer.MIN_VALUE);
        for (ListNode list : lists) {
            if (list != null) heap.offer(list);
        }
        ListNode curr = guard;
        while (heap.size() > 0) {
            ListNode x = heap.poll();
            ListNode nextX = x.next;
            curr.next = x;
            curr = x;
            if (nextX != null) { heap.offer(nextX);}
        }
        curr.next = null;
        return guard.next;
    }


    /**
     * Link list partition preserve same order.
     * Use guard, record node that prev node is more flexible than curr 
     */
    public ListNode partition(ListNode head, int x) {
        if (head == null || head.next == null) return head; // size == 1

        ListNode guard = new ListNode(-1);
        guard.next = head;
        
        ListNode slot = guard;
        for (ListNode prev = guard; prev != null && prev.next != null; prev = prev.next) {
            while (prev.next != null && prev.next.val < x) {
                if (prev.next == slot.next) {
                    slot = slot.next;
                    break;
                } else {
                    // cut
                    ListNode node = prev.next;
                    prev.next = prev.next.next;
                    // insert
                    node.next = slot.next;
                    slot.next = node;
                    // update
                    slot = node;
                }
            }
        }
        return guard.next;
    }

    /**
      * Remove last nth node from link list.
      * Use a guard node and a pre-move pointer. 
      */
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode guard = new ListNode(-1);
        guard.next = head;
        
        ListNode p1 = guard, p2 = head;
        while (n-- > 1) { p2 = p2.next;}
        assert(p2 != null);
        while(p2.next != null) {
            p1 = p1.next;
            p2 = p2.next;
        }
        p1.next = p1.next.next;
        return guard.next;
    }


    /**
     * Copy a link list with a random access pointer
     * Use a guard. Keep a map with old=>new nodes.
     */
    public RandomListNode copyRandomList(RandomListNode head) {
        Map<RandomListNode, RandomListNode> newNodeByNode = new HashMap<>();
        RandomListNode guard = new RandomListNode(-1);
        RandomListNode newTail = guard;
        for (RandomListNode curr = head; curr != null; curr = curr.next) {
            if (newNodeByNode.containsKey(curr)) {
                newTail.next = newNodeByNode.get(curr);
            } else {
                newTail.next = new RandomListNode(curr.label);
                newNodeByNode.put(curr, newTail.next);
            }
            newTail = newTail.next;
            if (curr.random != null) {
                if (newNodeByNode.containsKey(curr.random)) {
                    newTail.random = newNodeByNode.get(curr.random);
                } else {
                    newTail.random = new RandomListNode(curr.random.label);
                    newNodeByNode.put(curr.random, newTail.random);
                }
            }
        }
        
        return guard.next;
    }

    /**
      * switch 2n, 2n+1 node, n = [0, len/2]
      */
    public ListNode swapPairs(ListNode head) {
        if (head == null || head.next == null) return head;
        ListNode guard = new ListNode(-1);
        guard.next = head;
        ListNode prev = guard, curr = guard.next;
        while (curr != null && curr.next != null) {
            ListNode next = curr.next;
            
            curr.next = next.next;
            next.next = curr;
            prev.next = next;
            
            prev = curr;
            curr = curr.next; // curr is swapped
        }
        
        return guard.next;
    }


    private ListNode reverse(ListNode prevBlock) {
        ListNode curr = prevBlock.next, prev = null;
        ListNode newTail = curr;
        while (true) {
            ListNode tmpNext = curr.next;
            curr.next = prev;
            if (tmpNext == null) break;
            prev = curr;
            curr = tmpNext;
        }
        prevBlock.next = curr;
        return newTail;
    }
    /**
      * K group reverse linked list using guard.
      */
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode guard = new ListNode(-1);
        guard.next = head;
        int nodeCount = 0;
        ListNode prevBlock = guard, curr = null;
        for (curr = prevBlock.next; curr != null; curr = curr.next) {
            nodeCount ++;
            if (nodeCount == k) {
                ListNode nextBlock = curr.next;
                curr.next = null;//cut the tail
                curr = reverse(prevBlock);// curr is the next tail
                curr.next = nextBlock; // link the new tail
                prevBlock = curr;
                nodeCount = 0;   
            };
        }
        return guard.next;
    }
}
