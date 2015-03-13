#include<cstdio>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<cmath>
#include<string>
#include<vector>
using namespace std;
#define all(a) (a).begin(),(a).end()
#define mset(a,v) memset(a,v,sizeof(a))
#define sz(a) a.size()
#define pb push_back
#define rep(i,n) for(i=0;i<n;i++)
#define forr(i,a,b) for(i=a;i<=b;i++)
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

//typedef long long ll;
typedef vector<int> VI;
#define N 10000
int p[N];
//----------------------
class RunningLetters
{
public:
	int newsLength(vector <string> r)
	{
		// expand string
		// {"1 ba 3 c 2 ba"} =>{"bacbaba"}
		int i,j,n;
		string s="",a="",y="";		
		rep(i,sz(r)) s+=r[i];
		stringstream is(s);
		while(is>>n>>y){
			for(i=0;i<n;i++){
				a.insert(sz(a),y);
			}
		}
		// find shortest repeat
		forr(i,2,sz(a))
		{
			j=p[i-1];
			while(a[j]!=a[i-1]&&j>0) j=p[j];
			if(a[j]==a[i-1]) j++;
			p[i]=j;
		}
		return sz(a)-p[sz(a)];
	}
};
