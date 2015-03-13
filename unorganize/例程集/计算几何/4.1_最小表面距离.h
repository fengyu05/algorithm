#include <iostream>
#include <cmath>
using namespace std;
struct Point3D{
	double s[3];//x,y,z
	Point3D(){ s[0]=s[1]=s[2];}
};
#define INF 1e99
#define min(a,b) (a<b?a:b)
inline double sqr(double x){ return x*x; }
double dis(double x1,double y1,double x2,double y2){
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}
double L[3];//X,Y,Z ������߳�,��׼3D����
//���������� 0//3:ǰ�� 1//4:���� 2//5:����
// abs(a-b)==3 : a-b����
// a<3: �ɼ��� a>=3:͸����
int face(Point3D& x){//�ж�������һ����
	if(x.s[0]==L[0]) return 0;
	else if(x.s[0]==0) return 3;
	else if(x.s[1]==L[1]) return 1;
	else if(x.s[1]==0) return 4;
	else if(x.s[2]==L[2]) return 2;
	else return 5;
}
double on_face(Point3D& a,Point3D& b){
	double re=0;
	for(int i=0;i<3;i++) re+=sqr(a.s[i]-b.s[i]);
	return sqrt(re);
}
double near_face(Point3D a,Point3D b,int fa,int fb){
	double NL[3];
	memcpy(NL,L,sizeof(L));
	//͸������ɼ���ȼ�ӳ��
	if(fa>=3){//
		fa%=3;
		a.s[fa]=NL[fa];
		b.s[fa]=NL[fa]-b.s[fa];
	}
	if(fb>=3){//
		fb%=3;
		b.s[fb]=NL[fb];
		a.s[fb]=NL[fb]-a.s[fb];
	}
	if(fa>fb){ swap(fa,fb),swap(a,b);  }
	//������ת�ȼ۱任,ͬһת��Ϊfa=0,fb=1;
	if(fa==0&&fb==2){
		double cur[3]={0,NL[1],0};
		for(int i=0;i<3;i++){
			a.s[i]=abs(a.s[i]-cur[i]);
			b.s[i]=abs(b.s[i]-cur[i]);
		}
		swap(NL[1],NL[2]),swap(a.s[1],a.s[2]),swap(a.s[1],a.s[2]);
	}else if(fa==1&&fb==2){
		double cur[3]={NL[0],0,0};
		for(int i=0;i<3;i++){
			a.s[i]=abs(a.s[i]-cur[i]);
			b.s[i]=abs(b.s[i]-cur[i]);
		}
		swap(NL[0],NL[2]),swap(a.s[0],a.s[2]),swap(a.s[0],a.s[2]);
		swap(a,b);
	}
	// �Ƚ�����·��
	double r1=dis(a.s[1],a.s[2],NL[1]+NL[0]-b.s[0],b.s[2]);
	double r2=dis(a.s[1],a.s[2],NL[1]+NL[2]-b.s[2],NL[2]+NL[1]-b.s[1]);
	double r3=dis(a.s[1],NL[0]+a.s[2],NL[1]+b.s[2],b.s[0]);
	return min(min(r1,r2),r3);
}
double opp_face(Point3D& a,Point3D& b,int fa,int fb){
	return 0;
}
int main()
{	
	freopen("t.in", "r", stdin);
	scanf("%lf%lf%lf",&L[0],&L[1],&L[2]);
	Point3D a,b;
	scanf("%lf%lf%lf%lf%lf%lf",
		&a.s[0],&a.s[1],&a.s[2],&b.s[0],&b.s[1],&b.s[2]);
	int fa=face(a),fb=face(b);
	double re=0;
	if(fa==fb){//����
		re=on_face(a,b);
	}else if(abs(fa-fb)==3){//�����
		re=opp_face(a,b,fa,fb);
	}else{//������
		re=near_face(a,b,fa,fb);
	}
	printf("%.2lf\n",re);
	return 0;
}