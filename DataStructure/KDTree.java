
class Point {
  int k;
  int[] values;
}

class Node {
  int level;
  Point point;
  Node left, right;
  public Node(int level, Point point) {
    this.level = level;
    this.point = point;
  }
}


class KDTree {

  public Node init(List<Point> points, int depth) {
    if (points.size() == 0) return null;
    int k = points.get(0).point.k;
    int axis = depth % k;

    Collections.sort(points, new Comparator<Point>() {
      public int compare(Point x, Point y) {
        return x.values[axis] - y.values[axis];
      }
    });
    int mid = points.size() / 2;
    Node root = new Node(depth, points.get(mid));
    root.left = init(points.subList(0, mid), depth + 1);
    root.right = init(points.subList(mid + 1), depth + 1);;
    return root;
  }

  public Node insert(Point point, Node root) {
    int k = point.get(0).point.k;
    int axis = root.level % k;

    if (point.values[axis] < root.point.values[axis]) {
      if (root.left == null) {
        root.left = new Node(root.level+1, point);
        return root.left;
      } else {
        return insert(point, root.left);
      }
    } else {
      if (root.right == null) {
        root.right = new Node(root.level+1, point);
        return root.right;
      } else {
        return insert(point, root.right);
      }
    }
  }

  private Point findLeaf(Point x, Node root) {
    int k = point.get(0).point.k;
    int axis = root.level % k;

    if (point.values[axis] < root.point.values[axis]) {
      if (root.left != null) {
        return findLeaf(point, root.left);
      } else {
        return root;
      }
    } else {
      if (root.right != null) {
        return findLeaf(point, root.right);
      } else {
        return root;
      }
    }
  }

  public Point NearestNeighbourSearch(Point x, Node root) {
  }
}
