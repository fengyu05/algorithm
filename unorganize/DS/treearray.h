
#include <iostream>
using namespace std;
// poj 2352 star
const int N = 32100;
int c[N];//��״����

int lowBit(int x) {
    return x & (x ^ (x - 1));
}
void add(int x, int k) { // k can be negative 
    // a[x] += k
    while (x <= N) {
        c[x] += k;
        x += lowBit(x);
    }
}
int sum(int x) {
    //return sum(1..x);
    int ret = 0;
    while (x > 0) {
        ret += c[x];
        x -= lowBit(x);
    }
    return ret;
}
void init(){
	memset(c,0,sizeof(c));
}
int out[N],f[N];
void main(){
    int i,  x, y,n;    
    scanf("%d", &n);
    for (i=0; i<n; i++){
        scanf("%d%d", &x, &y);
        x++;// x=[1,INF) now
        add(x,1);// x can't be 0
        out[sum(x-1) + f[x]]++;
//�����xС�ĵ���+����x�ĵ���
        f[x]++;//����Ϊx�ĵ���++
    }
    for(i=0;i<n; i++)printf("%d\n",out[i]);   
}