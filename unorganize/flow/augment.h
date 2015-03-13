
//2: 下界约束最大流

	void sublow(int i,int j){ F.c[i][j]-=F.clow[i][j]; }
	void addlow(int i,int j){ F.c[i][j]+=F.clow[i][j];
							  F.f[i][j]+=F.clow[i][j];}
	void lower_bound_maxflow(int s,int t,int sd[],int n){
		//read data : init c[][] , clow[][]
		// while edge{i,j,caplow,cap} 
		// => c[i][j]=cap,clow[i][j]=caplow
		// sd[j]+=caplow,sd[i]-=caplow

		// add t-s edge 
		F.c[t][s]=INF;
		F.clow[t][s]=0;
		int i,j;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				sublow(i,j);
		}
		feasible(sd,n);
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				addlow(i,j);
		}
		F.V=n;
		//F.MaxFlow(s,t);
	}
//3: 下界约束最小流
//*/
int main()
{
	int sd[N]={4,2,1,-7};
	F.c[0][1]=3;  F.clow[0][1]=1;
	F.c[0][2]=5;  F.clow[0][2]=3;
	F.c[2][1]=3;  F.clow[2][1]=1;
	F.c[1][3]=4;  F.clow[1][3]=4;
	F.c[2][3]=3;  F.clow[2][3]=3;
	lower_bound_maxflow(0,3,sd,4);
    return 0;
}
/*
还是不懂，这个求下界约束的网络最大流算法步骤有问题吗？
1.根据边的下界流量统计出每一点的流量约束, sd[]  ＝总流出 －总流入
2.把各边容量减去下界流量 cap[][]-=caplow[][]
3.对每点的流量约束 sd[] 求可行流
4.把各边的下界流量加回去，cap[][]+=caplow[][] ,flow[][]+=caplow[][]
5,在这个基础上求 源点到汇的最大流

如果在这样的网络上计算，结果会是什么。运行到步骤2时，然后1-3 和2-3边的
容量为0，然后求可行流时会无解，但是这个网络很明显是有满足下界的最大流解的。
      0:源  3:汇         cap   caplow
			0      0-1 :  5      3
		   /  \    0-2 :  3      1
		  1 -- 2   1-2 :  3      1
		   \  /    1-3 :  3      3
			3      2-3 :  4      4

请教一下，谢谢

  */