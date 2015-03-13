#include <cstdio>

using namespace std;

int main(void)
{
#ifndef ONLINE_JUDGE
	freopen("f:\\Dev-Cpp\\acm_hit\\input.txt", "r", stdin);
#endif
 int input;
 int a[100000];
 while(scanf("%d\n",&input)==1){
   if(input==0) break;
   for(int i=1;i<=input;i++){
     scanf("%d",&a[i]);
   }
   
   bool am=true;
   for(int i=1;i<=input;i++){
      if(a[a[i]]!=i){
        am=false;
        break;
      }
   }
   if(am)
     printf("ambiguous\n");
   else
     printf("not ambiguous\n");
}
 
 return 0;   
}
