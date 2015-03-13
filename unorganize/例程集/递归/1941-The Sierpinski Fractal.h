/*
The Sierpinski Fractal
*/
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
#define N 3000

char map[N][N];

void Fractal(int size,int y,int x){
	if(size==1){
		map[y][x]=map[y+1][x-1]='/';
		map[y][x+1]=map[y+1][x+2]='\\';
		map[y+1][x]=map[y+1][x+1]='_';
		return;
	}else{
		int ofs = 1 << (size-1);
		Fractal(size-1,y,x);
		Fractal(size-1,y+ofs,x-ofs);
		Fractal(size-1,y+ofs,x+ofs);
	}
}
int main()
{	
	int n;	
	while(cin>>n,n){
		int y=1<<n;
		int x=y*2,i,j;
		memset(map,0,sizeof(map));
		for( i=0;i<y;i++){
			for( j=0;j<x;j++)
				map[i][j]=' ';
		}
		Fractal(n,0,y-1);
		for(i=0;i<y;i++){
			for(j=x-1;j>=0;j--){
				if(map[i][j]!=' '){
					map[i][j+1]=0;
					printf("%s\n",map[i]);
					break;
				}
			}
		}
		printf("\n");
	}
	return 0;
}
/* n=3
       /\
      /__\
     /\  /\
    /__\/__\
   /\      /\
  /__\    /__\
 /\  /\  /\  /\
/__\/__\/__\/__\
*/