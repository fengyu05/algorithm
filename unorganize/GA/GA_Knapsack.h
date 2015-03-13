#include<iostream>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;

#define N 32		//Population size
#define Len 32		//len of chromosome
#define GenCNT 32	// Max Generation
#define Elitism 1	// use Elitism

int w[Len],p[Len],cap;

char chro[N][Len],chro_next[N][Len];//chromosome
int fitness[N],ord[N];// fitness
int gen;//Generation
const int chro_size=Len;
void init(){
	for(int i=0;i<N;i++){
		memset(chro[i],0,sizeof(chro[i]));
		chro[i][ rand()%Len ] =1;
	}
}
class fun_cmp{
	// functor to sort ord with val in
	// another array
public:
	int *val;
	fun_cmp(int *arr):val(arr){}
	bool operator() (int x,int y) const {
		return val[x]>val[y];
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
		int wei=0;
		for(int j=0;j<Len;j++){
			fitness[i]+= p[j]*chro[i][j];
			wei+= w[j]*chro[i][j];
		}
		if(wei>cap) fitness[i]=0;
		tot_fit+=fitness[i];		
	}
	sort(ord,ord+N,fun_cmp(fitness));
	printf("-------------------------------------------------------------- %d Generation\n",gen);
	for(i=0;i<N;i++){
		print_chro(ord[i]);
	}
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
		memcpy(chro_next[cnt],chro[ord[idx]],chro_size);
		
		// Crossover
		if(isCrossover()){
			int idy=-1;
			while(y>0){
				idy++;
				y-=fitness[ ord[idy] ];			
			}
			if(idx!=idy){
				int break_point=rand()%Len;
				memcpy(chro_next[cnt]+break_point,
					chro[ord[idy]]+break_point,
					chro_size-break_point);
			}
		}

		// Mutation
		for(int pos=0;pos<Len;pos++)
			if(isMutation())
				chro_next[cnt][pos]=1-chro_next[cnt][pos];

		// Accepting
		int wei=0;
		for(int j=0;j<Len;j++){			
			wei+= w[j]*chro_next[cnt][j];
		}
		if(wei<=cap) cnt++;
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
	printf("wei\tval\n");
	for(i=0;i<N;i++){
		w[i]=rand()%1024,p[i]=rand()%1024;
		printf("%d\t%d\n",w[i],p[i]);
	}
	cap=(rand()%1024)*10;
	printf("cap: %d\n",cap);
	system("pause");

	int re=GA();
	printf("%d\n",re);
	return 0;
}