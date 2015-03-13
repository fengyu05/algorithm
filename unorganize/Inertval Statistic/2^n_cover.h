#include<iostream>
#include<algorithm>
#include<functional>
#include<cmath>
#include<cassert>
#include<vector>
using namespace std;

/*1 : use log(n) space to cal a^n in
	worst performent log(n).  
	just the same with binary cal(a^n)
	save a^1 a^2 a^4 ... a^log(n)
	cal(a^c) = rep c in binary,
	sum(a^(c:i)) the i digit in c(binary) 
*/
/*2: use ruler storage save a[1:n]
   to cal sum(i,j) in log(n)
   The idea of tree array.
*/
const int M=1<<16;
class tree_array{
public:	
	int c[M],size; // size must be the power of 2
	int lowBit(int x) {
		return x & (x ^ (x - 1));
	}
	void add(int x, int k) { // k can be negative 
		// a[x] += k
		while (x <= size) {
			c[x-1] += k;
			x += lowBit(x);
		}
	}
	int query(int x) {// sum:a[1..x];
		int ret = 0;
		while (x > 0) {
			ret += c[x-1];
			x -= lowBit(x);
		}
		return ret;
	}
	int query(int x,int y){ // sum:a(x..y]
		return query(y)-query(x);
	}
	int other(int x){ //sum:a(x..size]
		return c[size-1]-query(x);
	}
	void init(int maxsize){
		size=maxsize;
		memset(c,0,sizeof(c));
	}
};
int main()
{	
#ifndef ONLINE_JUDGE
	freopen("t.in", "r", stdin);
#endif

	return 0;
}