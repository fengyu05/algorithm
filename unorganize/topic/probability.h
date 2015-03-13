#pragma warning(disable: 4786) //for set
#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <set> 
using namespace std;

//-------------------------Random Number --------------------
// DIY edition
// a[0]=d
// a[n]=(b*a[n-1]+c)%m
typedef unsigned long uint;
typedef unsigned short uint16;
#define MAX 65536
#define MULTIPLIER 1194211693
#define ADDER 12345L

class randNum{
private:
	uint seed;
public:
	randNum(){	seed=time(0); }
	uint16 Random(uint n){
		seed=MULTIPLIER*seed+ADDER;
		return (uint16)((seed>>16)%n); 
	}
	double fRandom(){ 
		return Random(MAX)/double(MAX);
	}
};
// simple edition
//init: srand(time(0));
uint rand_uint(int n){ return rand()%n;}
double randF(){
	return rand()/(double)RAND_MAX;
}
// constant
const double PI=acos(-1.0); 
// -----------------------------------------------------------//
//------------------- normal distribution ----------------------
// ÃÜ¶Èº¯Êý f ~ 1/d*(sqrt(2*PI))*exp(-pow((x-a),2)/2*pow(d,2))
// a ~ Except value d ~ standar deviation
double Norm(){
	double s,t,p,q;
	while(1){
		s=2*randF()-1;
		t=2*randF()-1;
		p=s*s+t*t;
		if(p<1) break;
	}
	q=sqrt((-2*log(p))/p);
	return s*q;
}
double Norm(double a,double d){
	double x=Norm();
	return a+d*x;
}
//---------------------set element count-------------------------
// n ~ size , k ~ first time to repeat, k=sqrt(n*PI/2);
/*
typedef int Item;
typedef set<Item> SET;
int setsize(SET X){
	int k=0;SET S;
	Item a;
	do{
		a=uniform(X);
		S.insert(a);
		k++;
	}while(S.find(a)!=S.end());
	return 2*k*k/PI;
}*/
//--------------------check AB=C -------------------------------
// Mote p Æ«¼Ù
#define N 128 
void mult(int X[N][N],int a[N],int b[N],int n){
	// b=Xa
	for(int i=0;i<n;i++){
		b[i]=0;
		for(int j=0;j<n;j++)
			b[i]+=X[i][j]*a[j];
	}
}
int A[N][N],B[N][N],C[N][N];
bool check(int n){
	int x[N],y[N],z[N];
	for(int i=0;i<n;i++){
		x[i]=rand_uint(2);
		if(x[i]==0) x[i]=-1;
	}
	mult(B,x,y,n);
	mult(A,y,z,n);
	mult(C,x,y,n);
	for(int j=0;j<n;j++)
		if(y[j]!=z[j]) return false;
	return true;
}
//----------------------------------------------------------------
int main()
{	
	randNum a;
	srand(time(0));
	while(1){
		int cnt=0;
		for(int i=0;i<1000000;i++){
			double re=a.fRandom();
			if(re>0.5)
				cnt++;
		}
		printf("%d\n",cnt);
		system("pause");
	}
	return 0;
}