//1.ŷ������(phi)
const int mr=10000001;

int i,j,n,m,k;

bool notp[mr];
__int64 pr[670000];
int pn,ans;
int phi[mr];

void getphi()
{
	memset(notp,0,sizeof(notp));
	for(int i=2;i<mr;i++)
	{
  		if(!notp[i])
		{
			pr[pn++]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<pn && i*pr[j]<mr;j++)
		{
			int k=i*pr[j];
			notp[k]=1;
			if(i%pr[j]==0)
			{
				phi[k]=phi[i]*pr[j];
				break;
			}
			else
			{
				phi[k]=phi[i]*(pr[j]-1);
			}
		}
	}
}

//2.��Լ������(divnum)
/*
ɸ��i ��j������
���i|pr[j] ��ô divnum[i*pr[j]]=divsum[i]/(e[i]+1)*(e[i]+2)
���� divnum[i*pr[j]]=divnum[i]*divnum[pr[j]]

��i|pr[j]  e[i*pr[j]]=e[i]+1;
���� e[i*pr[j]]=1;
*/
const int mr=10000001;

int i,j,n,m,k;

bool notp[mr];
__int64 pr[670000];
int pn,ans;
int divnum[mr];
char e[mr];

void getdivnum()
{
	memset(notp,0,sizeof(notp));
	for(int i=2;i<mr;i++)
	{
  		if(!notp[i])
		{
			pr[pn++]=i;
			e[i]=1;
			divnum[i]=2;
		}
		for(int j=0;j<pn && i*pr[j]<mr;j++)
		{
			int k=i*pr[j];
			notp[k]=1;
			if(i%pr[j]==0)
			{
				divnum[k]=divnum[i]/(e[i]+1)*(e[i]+2);
				e[k]=e[i]+1;
				break;
			}
			else
			{
				divnum[k]=divnum[i]*divnum[pr[j]];
				e[k]=1;
			}
		}
	}
}
/**
APP:
POJ 2773 Happy 2006
����������m�����m��ŷ������ֵv������֪��1 ~ m֮����m���ص����ĸ���Ϊv��
����m + 1 ~ 2m, 2m + 1 ~ 3m, 3m + 1 ~ 4m����.�����������v����m���ʵ�������
**/