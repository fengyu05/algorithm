//完成极大极小过程
//井字过三关
#include <iostream>

using namespace std;
// 1 win , -1 lost , 0 draw
char map[3][3];
int end(){
	int i;
	for(i=0;i<3;i++){
		char c=map[i][0];
		if(c!=0&&c==map[i][1]&&c==map[i][2]){
			return (c=='O')?1:-1;
		}
	}
	for(i=0;i<3;i++){
		char c=map[0][i];
		if(c!=0&&c==map[1][i]&&c==map[2][i]){
			return (c=='O')?1:-1;
		}
	}
	char c=map[1][1];
	if(c!=0&&map[0][0]==c&&c==map[2][2])
		return (c=='O')?1:-1;
	if(c!=0&&map[0][2]==c&&c==map[2][0])
		return (c=='O')?1:-1;
	return 0;
}
int search(int player,int lv,int prune){//player 1/-1
	int val=end();
	if(val!=0) return val;
	if(lv==9) return 0;
	int _max=-1,_min=1;
	for(int i=0;i<9;i++){
		int x=i/3,y=i%3;
		if(map[x][y]==0){
			map[x][y]=(player==1)?'O':'X';
			int tmp=search(-player,lv+1,(player==1)?_max:_min);
			map[x][y]=0;
			if(player==-1&&tmp<prune) return tmp;// a-b prune
			if(player==1&&tmp>prune) return tmp;
			if(tmp>_max) _max=tmp;
			if(tmp<_min) _min=tmp;
		}
	}
	return (player==1)?_max:_min;
}
void print(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(map[i][j]==0) printf("-");
			else printf("%c",map[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	int cas;
	scanf("%d",&cas);
	while(cas--){
		memset(map,0,sizeof(map));
		int x1,y1,x2,y2;
		x1=rand()%3,y1=rand()%3;
		map[x1][y1]='O';
		x2=rand()%3,y2=rand()%3;
		map[x2][y2]='X';
		if(x1==x2&&y1==y2) continue;
		print();
		printf("%d\n",search(1,2,1));// player==-1 prune=_min=1
	printf("________________\n");
	}
	return 0;
}


//完成极大极小过程 + a-b剪枝
// Poj 3527 Generalized Connect Four
#include <iostream>
using namespace std;
#define N 10
// 1 'B' win ,  -1 'B' lost , 0 draw
char map[N][N];
int n,m;
int ofs[8][2]={
	-1,0,//N  0
	-1,1,//NE 1
	 0,1,//E  2
	 1,1,//SE 3
	 1,0,//S  4
	1,-1,//SW 5
	 0,-1,//W  6
	-1,-1//NW 7
};
bool win(int x,int y,char c){
	char d[8]={0};
	for(int i=0;i<8;i++){
		int nx=x,ny=y;
		while(1){
			nx+=ofs[i][0],ny+=ofs[i][1];
			if(map[nx][ny]!=c) break;
			else d[i]++;
		}
	}
	for(int j=0;j<4;j++){
		if(d[j]+d[j+4]+1>=4) return true;
	}return false;

	return 0;
}
int search(int player,int lv,int prune){//player 1/-1
	if(lv==n*m) return 0;
	int i;
	char c=(player==1)?'B':'W';
	for(i=1;i<=m;i++) if(map[1][i]=='.'){
		int x=n,y=i;
		while(map[x][y]!='.'){x--;}
		if(win(x,y,c)) return player;//win
	}
	int re=(player==1)?-1:1;
	for(i=1;i<=m;i++) if(map[1][i]=='.'){
		int x=n,y=i;
		while(map[x][y]!='.'){x--;}
		map[x][y]=c;
		int tmp=search(-player,lv+1,re);
		map[x][y]='.';
		if(player==-1&&tmp<prune) return tmp;// a-b prune
		if(player==1&&tmp>prune) return tmp;
		if(player==1&&tmp>re){
			re=tmp;
			if(re==1) break;// best found
		}
		if(player==-1&&tmp<re){
			re=tmp;
			if(re==-1) break;// best found
		}
	}
	return re;
}
void print(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	while(scanf("%d%d",&n,&m)==2){
		memset(map,0,sizeof(map));
		int i,j;
		int cnt=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++){
				while(scanf("%c",&map[i][j]),map[i][j]=='\n');
				if(map[i][j]!='.') cnt++;
			}
		print();
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++){
				if(map[i][j]!='.'&&win(i,j,map[i][j])){
					if(map[i][j]=='B') printf("Black Wins!\n");
					else printf("White Wins!\n");
					return 0;
				}
			}
		int player=(cnt%2==0)?1:-1;
		int re=search(player,cnt,player);// prune=player
		if(re==1) printf("Black Wins!\n");
		else if(re==-1) printf("White Wins!\n");
		else printf("Draw!\n");
	}
	return 0;
}