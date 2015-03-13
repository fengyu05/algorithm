// Problem   Flavius Josephus POJ 2939
// Algorithm Pollard Rho
// Runtime   O(n)
/*
Advance one pointer in steps of two, another pointer in steps of one.
 When they point to the same soldier, we know that this is one of the
 soldiers who will commit suicide. Every soldier whose number is calc
 ulated after that will commit suicide as well.
*/
#include <stdio.h>
#include <assert.h>

int next(long long cur, long long a, long long b, long long n) {
	return (a*((cur*cur)%n)+b)%n;
}

int main() {
	int n,a,b;
	while(scanf("%d",&n) == 1 && n != 0) {
		assert(scanf("%d %d",&a,&b) == 2);
		assert(a >= 0 && a < n && b >= 0 && b < n);
		int p1 = 0, p2 = 0, len = 0;
		int cnt = 0;
		// find a value in the cycle
		do {
			p1 = next(p1,a,b,n); // advance pointer 1 in steps of 1
			p2 = next(next(p2,a,b,n),a,b,n); // advance pointer 2 in steps of 2
			++cnt;
		}while(p1 != p2);
		// find cycle length
		do {
			p2 = next(p2,a,b,n);
			++len;
		}while(p1 != p2);
		printf("%d\n",n-len);
	}
	return 0;
}