#include <iostream>
using namespace std;

#define M 10
struct node{
	node* chi[M];
	int end;
	node(){ 
		end=0;
		memset(chi,0,sizeof(chi));
	}
};
//typedef node* link;

node* root;
void init(){
	root=new node;
}
bool insert(char str[]){
	node* ptr=root;
	int count=0;
	for(int i=0;str[i];i++){
		if(ptr->end==1) return false;
		int dex=str[i]-'0';
		if(ptr->chi[dex]==0){
			ptr->chi[dex]=new node;
			count++;
		}
		ptr=ptr->chi[dex];
	}
	ptr->end=1;
	return count>0;
}
int main()
{
	char str[16];
	int cas,n;
	scanf("%d",&cas);
	while(cas--){
		scanf("%d",&n);
		init();
		bool re=true;
		for(int i=0;i<n;i++){
			scanf("%s",str);
			if(re)
				if(!insert(str))
					re=false;
		}
		if(re) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}