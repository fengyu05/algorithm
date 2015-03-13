#include<iostream>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;

#define N 128		//Population size
#define Len 128		//len of chromosome
#define GenCNT 32	// Max Generation
#define Elitism 1	// use Elitism

int mat[Len][Len];

#define INF 1000000000 
int n;
int	x[Len];//当前解
int	bestx[Len];//最优解
int	cc,bestc; //当前费用，最优费用

void init2(){
	cc=0;bestc=INF;
	for(int i=1;i<n;i++)
		x[i]=i;
}

void search(int i)
{
	if(i==n-1){
		if(cc+mat[ x[n-2] ][ x[n-1] ]+mat[ x[n-1] ][ 0 ]<bestc){
			for(int j=0;j<n;j++)
				bestx[j]=x[j];
			bestc=cc+mat[ x[n-2] ][ x[n-1] ]+mat[ x[n-1] ][ 0 ];
		}
	}else{
		for(int j=i;j<n;j++){
			if(cc+mat[ x[i-1] ][ x[j] ]<bestc){
				swap(x[i],x[j]);
				cc+=mat[ x[i-1] ][ x[i] ];
				search(i+1);
				cc-=mat[ x[i-1] ][ x[i] ];
				swap(x[i],x[j]);
			}
		}
	}
}

char chro[N][Len],chro_next[N][Len];//chromosome
int fitness[N],ord[N];// fitness
int gen;//Generation
const int chro_size=Len;
void init(){
	for(int i=0;i<N;i++){
		for(int j=0;j<Len;j++) chro[i][j]=j;
		random_shuffle(chro[i],chro[i]+Len);
	}
}
class fun_cmp{
	// functor to sort ord with val in
	// another array
public:
	int *val;
	fun_cmp(int *arr):val(arr){}
	bool operator() (int x,int y) const {
		return val[x]<val[y];
	}
};
//Crossover rate 80%
bool isCrossover(){ return (rand()%10000)<8000;}
//Mutation rate 3% at each locus
bool isMutation(){ return (rand()%10000<300); }

void print_chro(int x){
	for(int i=0;i<Len;i++)
		printf("%d",chro[x][i]);
	printf("\t\t%d\n",fitness[x]);
}
int cal_fit(){
	int tot_fit=0,i;
	for(i=0;i<N;i++){
		fitness[i]=0;ord[i]=i;
		for(int j=0;j<Len;j++){
			fitness[i]+= mat[chro[i][j]][chro[i][(j+1)%Len]] ;
		}
		tot_fit+=fitness[i];		
	}
	sort(ord,ord+N,fun_cmp(fitness));
	/*
	printf("-------------------------------------------------------------- %d Generation\n",gen);
	for(i=0;i<N;i++){
		print_chro(ord[i]);
	}//*/
	return tot_fit;
}

void gen_next(int tot){
	int cnt=0;
	if(Elitism)
		memcpy(chro_next[cnt++],chro[ord[0]],chro_size);
	while(cnt<N){
		
		// Selection
		int x=rand()%tot,y=rand()%tot;
		int idx=-1;
		while(x>0){
			idx++;
			x-=fitness[ ord[idx] ];			
		}
		if(idx==-1) idx=N-1;
		memcpy(chro_next[cnt],chro[ord[idx]],chro_size);
		
		// Crossover
		if(isCrossover()){
			int idy=-1;
			while(y>0){
				idy++;
				y-=fitness[ ord[idy] ];			
			}
			if(idy==-1) idy=N-1;
			if(idx!=idy){
				int break_point=rand()%Len;
				bool has[Len]={0};
				int k;
				for(k=0;k<break_point;k++)
					has[chro_next[cnt][k]]=1;
				for(k=0;k<Len;k++){
					int id=chro[ord[idy]][k];
					if(has[id]==0)
						chro_next[cnt][break_point++]=id;
				}
			}
		}

		// Mutation

		for(int pos=0;pos<Len;pos++)
			if(isMutation()){
				int pos1=rand()%Len,pos2=rand()%Len;
				swap(chro_next[cnt][pos1],chro_next[cnt][pos2]);
			}
		// Accepting
		cnt++;
	}
	memcpy(chro,chro_next,sizeof(chro));
}

int GA(){
	init(); // rand to create init population
	gen=0;
	while( gen++ <GenCNT){
		// calculate and sort fitness
		int tot_fit=cal_fit();
		// gen New population
		gen_next(tot_fit);
	}
	cal_fit();
	return fitness[ord[0]];
}
int main()
{
	int i;
	for(i=0;i<Len;i++){
		for(int j=0;j<Len;j++)
			mat[i][j]=rand();
	}
	
	int re=GA();
	printf("%d\n",re);
	
	n=Len;
	init2();
	search(1);
	re=0;
	for(i=0;i<n;i++) re+=mat[bestx[i]][bestx[(i+1)%n]];
	printf("%d\n",re);
	return 0;
}