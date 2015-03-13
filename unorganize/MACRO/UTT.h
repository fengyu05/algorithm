#ifndef MACRO_UTT_H
#define MACRO_UTT_H
// for vc++ 6
#pragma warning(disable: 4786)
#pragma warning(disable: 4101) 
// include
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctype.h>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <complex>
#include <cstdio>
#include <cassert>
#include <cmath>
using namespace std;
// define
#define CLEAR(x,c) memset(x,c,sizeof(x)) 
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define SIZE(a) (int(a.size()))
#define REIN(fi) freopen(fi, "r", stdin)
#define REOUT(fi) freopen(fi, "w", stdout)
#define ALL(x) (x).begin(),(x).end()
#define SORT(x) sort(ALL(x))
#define REVERSE(x) reverse(ALL(x))

// for iteration :be careful when use
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;i++)
#define REP(i,n) FOR(i,0,(n)-1)
#define FORALL(i,c) REP(i,SIZE(c))
#define FORDECR(i,a,b) for(int i=(a),_b=(b);i>=_b;i--)

#define sz size()
#define pb push_back
#define mp make_pair
#define X first
#define Y second

// typedef
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef vector<pair<int,int> > VII;
typedef set<string> SI;

typedef VI::iterator VIT;
typedef SI::iterator SIT;

// handle __int64 and long long
#ifdef WIN32
typedef signed __int64 i64;
typedef unsigned __int64 u64;
istream& operator>>(istream& s, i64& d){
	char b[30];	s>>b;
	sscanf(b, "%I64d", &d);	return s;                          
}                                      
ostream& operator<<(ostream& s, i64 d){
	char b[30];	sprintf(b,"%I64d",d);
	s<<b;	return s;                          
} 
#else
typedef signed long long i64;
typedef unsigned long long u64;
#endif
//-----------------------------------------------------
// function
template<class T> T gcd(T x, T y) {return x ? gcd(y%x,x) : y;}
i64 s2i(string s){ istringstream i(s); i64 x; i>>x; return x; }
template<class T> string i2s(T x) { ostringstream o; o << x; return o.str(); }
template<class T> int bitcnt(T r) {return r == 0 ? 0 : (bitcnt(r>>1) + (r&1));}
#endif