
//2 sum O(nlogn)
// The prove of never miss.
// if ax + ay = target
// if exist a miss of ax, then
// ax + by < target, if won't happen because by < ay, ay will be found before
// this miss.

public towSum(int[] num, int target) {
  sort(num);
  int i = starting; //头指针
  int j = num.size() - 1; //尾指针
  while(i < j) {
      int sum = num[i] + num[j];
      if(sum == target) {
          store num[i] and num[j] somewhere;
          if(we need only one such pair of numbers)
              break;
          otherwise
              do ++i, --j;
      }
      else if(sum < target)
          ++i;
      else
          --j;
  }
}

// 3 sum O(n^2)
// sorted + enumerate a1, reduce to 2 sum

public ArrayList<ArrayList<Integer>> threeSum(int[] num) {
  ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>>();
 
  if (num.length < 3)
    return result;
 
  // sort array
  Arrays.sort(num);
 
  for (int i = 0; i < num.length - 2; i++) {
    // //avoid duplicate solutions
    if (i == 0 || num[i] > num[i - 1]) {
 
      int negate = -num[i];
 
      int start = i + 1;
      int end = num.length - 1;
 
      while (start < end) {
        //case 1
        if (num[start] + num[end] == negate) {
          ArrayList<Integer> temp = new ArrayList<Integer>();
          temp.add(num[i]);
          temp.add(num[start]);
          temp.add(num[end]);
 
          result.add(temp);
          start++;
          end--;
          //avoid duplicate solutions
          while (start < end && num[end] == num[end + 1])
            end--;
 
          while (start < end && num[start] == num[start - 1])
            start++;
        //case 2
        } else if (num[start] + num[end] < negate) {
          start++;
        //case 3
        } else {
          end--;
        }
      }
 
    }
  }
  return result;
}


public ArrayList<ArrayList<Integer>> fourSum(int[] num, int target) {
  int len = num.length;
  ArrayList<ArrayList<Integer>> result = new ArrayList<>();
  if(len < 4) return result;
  Arrays.sort(num);
  for (int i = 0; i < len; i++) {
    if (i > 0 && num[i] == num[i-1]) continue;//filter duplicate
    for (int j = i + 1; j < len; j++) {
      if (j > i + 1 && num[j] == num[j-1]) continue; //filter duplicate
      int targetSum = target - num[i] - num[j];
      int start = j + 1;
      int end = len - 1;
      while (start < end) {
        if (num[start] + num[end] == targetSum) {
          ArrayList<Integer> solu = new ArrayList<>();
          solu.add(num[i]);
          solu.add(num[j]);
          solu.add(num[start]);
          solu.add(num[end]);
          result.add(solu);
          start++;
          end--;

          while (start < end && num[start] == num[start-1]) start++;//remove duplicate
          while (start < end && num[end] == num[end+1]) end--; //remove duplicate
        } else if (num[start] + num[end] < targetSum) {
          start++;
        } else {
          end--;
        }
      }
    }
  }
  return result;
}
