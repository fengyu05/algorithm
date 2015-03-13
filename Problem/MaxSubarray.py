
# Kadane's algorithm consists
def max_subarray(A):
  max_ending_here = max_so_far = 0
  for x in A:
    max_ending_here = max(0, max_ending_here + x)
    max_so_far = max(max_so_far, max_ending_here)
  return max_so_far

#
# A variation of the problem that does not allow zero-length
#subarrays to be returned in the case that the entire array consists of
#negative numbers can be solved with the following code:
def max_subarray(A):
  max_ending_here = max_so_far = A[0]
  for x in A[1:]:
    max_ending_here = max(x, max_ending_here + x)
    max_so_far = max(max_so_far, max_ending_here)
  return max_so_far
