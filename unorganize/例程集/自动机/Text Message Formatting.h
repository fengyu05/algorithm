/*
3583Text Message Formatting

sample:
Last {1} login attempts by {2}
20
frkstyc
//
 use \ escaped.
*/
#include <iostream>
using namespace std;
#define N 128
template<class Item,int __SIZE>class Queue{
public:
	Item array[__SIZE];
	int front,rear;
	void init(){front=-1,rear=-1;}
	int next(int pos){return (pos+1)%__SIZE;}
	void push(Item x){ array[rear=next(rear)]=x;}
	Item pop(){ return array[front=next(front)];}
	int size(){ return rear-front;}
} ;
Queue<char,N> que;
char dic[1000][N];
int cnt;
//automate
int charId(char c){
	if(c=='\\') return 0;
	if(c=='{') return 1;
	if(c=='}') return 2;
	if(c>='0'&&c<='9') return 3;
	else return 4;
}
char act[4][5][4]={ "1--","i2-","*0-","*0-","*0-",
					"*0-","*0-","*0-","*0-","*0-",
					"o1-","oi2","o*0","i_3","o*0",
					"o1-","oi2","ix0","in3","o*0"
	
};
void go(char str[]){
	int stat=0;
	int num=0;
	que.init();
	for(int i=0;str[i];i++){
		int id=charId(str[i]);
		for(int j=0;j<4;j++){
			char cc=act[stat][id][j];
			if(cc>='0'&&cc<='3'){
				stat=cc-'0';
				break;
			}else if(cc=='*'){
				putchar(str[i]);
			}else if(cc=='i'){
				que.push(str[i]);
			}else if(cc=='o'){
				while(que.size()){
					putchar(que.pop());
				}
			}else if(cc=='_'){
				num=str[i]-'0';
			}else if(cc=='x'){
				if(num-1<cnt){
					printf("%s",dic[num-1]);
					que.init();
				}else{
					while(que.size()){
						putchar(que.pop());
					}				
				}
			}else if(cc=='n'){
				num=num*10+str[i]-'0';
				if(num<=1000){
					continue;
				}else{
					stat=0;
					break;
				}
			}else break;
		}
	}
}
int main()
{	
	char str[128];
	gets(str);
	cnt=0;
	while(gets(dic[cnt])){
		cnt++;
	}
	go(str);
	printf("\n");
	return 0;
}