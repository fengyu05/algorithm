
//2: �½�Լ�������

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
//3: �½�Լ����С��
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
���ǲ�����������½�Լ��������������㷨������������
1.���ݱߵ��½�����ͳ�Ƴ�ÿһ�������Լ��, sd[]  �������� ��������
2.�Ѹ���������ȥ�½����� cap[][]-=caplow[][]
3.��ÿ�������Լ�� sd[] �������
4.�Ѹ��ߵ��½������ӻ�ȥ��cap[][]+=caplow[][] ,flow[][]+=caplow[][]
5,������������� Դ�㵽��������

����������������ϼ��㣬�������ʲô�����е�����2ʱ��Ȼ��1-3 ��2-3�ߵ�
����Ϊ0��Ȼ���������ʱ���޽⣬�������������������������½���������ġ�
      0:Դ  3:��         cap   caplow
			0      0-1 :  5      3
		   /  \    0-2 :  3      1
		  1 -- 2   1-2 :  3      1
		   \  /    1-3 :  3      3
			3      2-3 :  4      4

���һ�£�лл

  */