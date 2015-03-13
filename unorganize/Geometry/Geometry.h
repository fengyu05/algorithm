

 
//<��>�߶μ�ֱ�ߵĻ������� 
 
/* �жϵ�C���߶�AB���ڵ�ֱ��l�ϴ���P�����߶�AB�Ĺ�ϵ  
�������Ǹ�������Ĺ�ʽд��,P�ǵ� C���߶�AB����ֱ�ߵĴ���  
                AC dot AB  
        r =     ---------------------- 
                 ||AB||^2  
               (Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay)  
          =    ----------------------------------------------------  
                          L^2  
    r has the following meaning:  
        r=0      P = A  
        r=1      P = B  
        r<0      P is on the backward extension of AB  
		r>1      P is on the forward extension of AB  
        0<r<1    P is interior to AB  
*/  
double relation(Point c,LineSeg l)  
{  
	LineSeg tl;
	tl.s=l.s;
	tl.e=c;
	return dotmultiply(tl.e,l.e,l.s)/(dist(l.s,l.e)*dist(l.s,l.e));
}
 
// ���C���߶�AB ����ֱ�ߵĴ��� P  
Point perpendicular(Point p,LineSeg l)  
{  
	double r=relation(p,l);
	Point tp;
	tp.x=l.s.x+r*(l.e.x-l.s.x);
	tp.y=l.s.y+r*(l.e.y-l.s.y);
	return tp;
}
 
/* ���p���߶�l����̾��� 
�����߶��Ͼ�õ�����ĵ�np ע�⣺np���߶�l�ϵ���p����ĵ�,��һ���Ǵ��� */  
double ptolinesegdist(Point p,LineSeg l,Point &np)  
{  
	double r=relation(p,l);
	if(r<0)  
	{  
		np=l.s;
		return dist(p,l.s);
	}
	if(r>1)  
	{  
		np=l.e;
		return dist(p,l.e);
	} 
	np=perpendicular(p,l);
	return dist(p,np);
}
 
// ���p���߶�l����ֱ�ߵľ��� 
//��ע�Ȿ�������ϸ�����������   
double ptoldist(Point p,LineSeg l)  
{  
	return abs(multiply(p,l.e,l.s))/dist(l.s,l.e);
}
 
/* ����㵽���߼����������,�����������.  
ע�⣺���õ���ptolineseg()���� */  
double ptoPointset(int vcnt, Point Pointset[], Point p, Point &q)  
{  
	int i;
	double cd=double(INF),td;
	LineSeg l;
	Point tq,cq;
 
	for(i=0;i<vcnt-1;i++)  
	{  
		l.s=Pointset[i];
		l.e=Pointset[i+1];
		td=ptolinesegdist(p,l,tq);
		if(td<cd)  
		{  
			cd=td;
			cq=tq;
		}
	}
	q=cq;
	return cd;
}
 
/* �ж�Բ�Ƿ��ڶ������*/  
bool CircleInsidePolygon(int vcnt,Point center,double radius,Point polygon[])  
{  
	Point q;
	double d;
	q.x=0;
	q.y=0;
	d=ptoPointset(vcnt,polygon,center,q);
	if(d<radius||fabs(d-radius)<EP) return true;
	else return false;
}
 
/* ��������ʸ��l1 ��l2�ļнǵ����� (-1 ~ 1) 
ע�⣺������������нǵĻ�,ע�ⷴ���Һ�����ֵ���Ǵ� 0��pi */  
double cosine(LineSeg l1,LineSeg l2)  
{  
	return(((l1.e.x-l1.s.x)*(l2.e.x-l2.s.x)+(l1.e.y-l1.s.y)*(l2.e.y-l2.s.y))
		/(dist(l1.e,l1.s)*dist(l2.e,l2.s)) );
}
 
// �����߶� l1��l2 ֮��ļн�  
//��λ������ ��Χ(-pi,pi)  
double lsangle(LineSeg l1,LineSeg l2)  
{  
	Point o,s,e;
	o.x=o.y=0;
	s.x=l1.e.x-l1.s.x;
	s.y=l1.e.y-l1.s.y;
	e.x=l2.e.x-l2.s.x;
	e.y=l2.e.y-l2.s.y;
	return angle(o,s,e);
}

 

 
// ����߶� l1��l2 �ཻ,����true �ҽ�����(inter)����,���򷵻�false  
bool intersection(LineSeg l1,LineSeg l2,Point &inter)  
{  
	Line ll1,ll2;
	ll1=makeline(l1.s,l1.e);
	ll2=makeline(l2.s,l2.e);
	if(lineintersect(ll1,ll2,inter)) return online(l1,inter);
	else return false;
}
 
//<��> ����γ����㷨ģ��  
//������ر�˵��,�������ζ���Ҫ����ʱ������  
// ���ض�������(signed); 
// ���붥�㰴��ʱ������ʱ,������ֵ;���򷵻ظ�ֵ  
double area_of_polygon(int vcnt,Point polygon[])  
{  
	int i;
	double s;
	if (vcnt<3)  
	   return 0;
	s=polygon[0].y*(polygon[vcnt-1].x-polygon[1].x);
	for (i=1;i<vcnt;i++)  
	s+=polygon[i].y*(polygon[(i-1)].x-polygon[(i+1)%vcnt].x);
	return s/2;
}
// �ж϶����Ƿ���ʱ������ 
// ������붥�㰴��ʱ������,����true  
bool isconterclock(int vcnt,Point polygon[])  
{  
	return area_of_polygon(vcnt,polygon)>0;
}
 
/*���߷��жϵ�q������polygon ��λ�ù�ϵ 
Ҫ��polygon Ϊ�򵥶����,����ʱ������  
������ڶ�����ڣ�  ����0  
������ڶ���α��ϣ�����1  
������ڶ�����⣺  ����2 */  
int insidepolygon(Point q,int vcnt,Point Polygon[]) 
{  
	int c=0,i,n; 
	LineSeg l1,l2; 
  
	l1.s=q; l1.e=q;l1.e.x=double(INF); 
	n=vcnt;
 
	for (i=0;i<vcnt;i++)  
	{  
		l2.s=Polygon[i];
		l2.e=Polygon[(i+1)%vcnt]; 
   
		double ee= Polygon[(i+2)%vcnt].x; 
		double ss= Polygon[(i+3)%vcnt].y; 
 
		if(online(l2,q)) 
			return 1;     
		if(intersect_A(l1,l2)) 
			c++;  // �ཻ�Ҳ��ڶ˵�  
 
        if(online(l1,l2.e)&& !online(l1,l2.s) && l2.e.y>l2.e.y) 
			c++;//l2��һ���˵��� l1���Ҹö˵������˵���������ϴ���Ǹ� 
		if(!online(l1,l2.e)&& online(l1,l2.s) && l2.e.y<l2.e.y) 
			c++;//����ƽ�б� 
	}
	if(c%2 == 1)  
		return 0;
    else  
		return 2; 
} 
 
//�жϵ�q��͹�����polygon �� 
// ��q��͹�����polygon ��[��������]ʱ,����true 
// ע�⣺�����polygon һ��Ҫ��͹�����   
bool InsideConvexPolygon(int vcnt,Point polygon[],Point q)  
{  
	Point p;
	LineSeg l;
	int i;
	p.x=0; p.y=0;
	for(i=0;i<vcnt;i++) // Ѱ��һ���϶��ڶ����polygon �ڵĵ�p������ζ���ƽ��ֵ  
	{  
		p.x+=polygon[i].x;
		p.y+=polygon[i].y;
	}
	p.x /= vcnt;
	p.y /= vcnt;
 
	for(i=0;i<vcnt;i++)  
	{  
		l.s=polygon[i]; 
		l.e=polygon[(i+1)%vcnt];
		if(multiply(p,l.e,l.s)*multiply(q,l.e,l.s)<0)  
		/* ��p�͵�q�ڱ� l ������,˵����q�϶��ڶ������ */  
		return false; 
	}
	return true; 
}
 
/*Ѱ��͹���� graham ɨ�跨  
PointSet Ϊ����ĵ㼯;  
chΪ�����͹���ϵĵ㼯,������ʱ�뷽������;
nΪPointSet �еĵ����Ŀ  
lenΪ�����͹���ϵĵ�ĸ��� */  
void Graham_scan(Point PointSet[],Point ch[],int n,int &len)  
{  
	int i,j,k=0,top=2;
	Point tmp;
	// ѡȡPointSet ��y������С�ĵ�PointSet[k],��������ĵ��ж��,��ȡ����ߵ�һ��  
	for(i=1;i<n;i++)  
		if ( PointSet[i].y<PointSet[k].y || (PointSet[i].y==PointSet[k].y) 
			&& (PointSet[i].x<PointSet[k].x) )  
				k=i;
	tmp=PointSet[0];
	PointSet[0]=PointSet[k];
	PointSet[k]=tmp; // ����PointSet ��y������С�ĵ���PointSet[0]  
	for (i=1;i<n-1;i++) /* �Զ��㰴�����PointSet[0]�ļ��Ǵ�С�����������,������ͬ  
	�İ��վ���PointSet[0]�ӽ���Զ�������� */  
	{  
		k=i;
		for (j=i+1;j<n;j++)  
			if ( multiply(PointSet[j],PointSet[k],PointSet[0])>0 ||    // ���Ǹ�С     
			  (multiply(PointSet[j],PointSet[k],PointSet[0])==0) &&  /* �������,�������  */     
				dist(PointSet[0],PointSet[j])<dist(PointSet[0],PointSet[k]) )  
					k=j;
		tmp=PointSet[i];
		PointSet[i]=PointSet[k];
		PointSet[k]=tmp;
	}
	ch[0]=PointSet[0];
	ch[1]=PointSet[1];
	ch[2]=PointSet[2];
	for (i=3;i<n;i++)  
	{  
		while (multiply(PointSet[i],ch[top],ch[top-1])>=0) top--;
		ch[++top]=PointSet[i];
	}
	len=top+1;
}
 
// ���������㼯͹��,����˵��ͬgraham �㷨     
void ConvexClosure(Point PointSet[],Point ch[],int n,int &len)  
{  
	int top=0,i,index,first;
	double curmax,curcos,curdis;
	Point tmp;
	LineSeg l1,l2;
	bool use[MAXV];
	tmp=PointSet[0];
	index=0;
	// ѡȡy��С��,�������һ��,��ѡȡ�����  
	for(i=1;i<n;i++)  
	{  
		if(PointSet[i].y<tmp.y||PointSet[i].y == tmp.y&&PointSet[i].x<tmp.x)  
		{  
			index=i;
		}
		use[i]=false;
	}
	tmp=PointSet[index];
	first=index;
	use[index]=true;
 
	index=-1;
	ch[top++]=tmp;
	tmp.x-=100;
	l1.s=tmp;
	l1.e=ch[0];
	l2.s=ch[0];
 
	while(index!=first)  
	{  
		curmax=-100;
		curdis=0;
		// ѡȡ�����һ��ȷ���߼н���С�ĵ�,������ֵ�����  
		for(i=0;i<n;i++)  
		{  
			if(use[i])continue;
			l2.e=PointSet[i];
			curcos=cosine(l1,l2); // ����cosֵ��н�����,��Χ�� ��-1 -- 1 ��  
			if(curcos>curmax || fabs(curcos-curmax)<1e-6 && dist(l2.s,l2.e)>curdis)  
			{  
				curmax=curcos;
				index=i;
				curdis=dist(l2.s,l2.e);
			} 
		}
		use[first]=false;   //��յ�first �������־,ʹ������γɷ�յ�hull  
		use[index]=true;
		ch[top++]=PointSet[index];
		l1.s=ch[top-2];
		l1.e=ch[top-1];
		l2.s=ch[top-1];
	}
	len=top-1;
}
// ��͹����ε�����,Ҫ���������ΰ���ʱ������  
Point gravitycenter(int vcnt,Point polygon[])  
{  
	Point tp;
	double x,y,s,x0,y0,cs,k;
	x=0;y=0;s=0;
	for(int i=1;i<vcnt-1;i++)  
	{  
		x0=(polygon[0].x+polygon[i].x+polygon[i+1].x)/3;
		y0=(polygon[0].y+polygon[i].y+polygon[i+1].y)/3; //��ǰ�����ε�����  
		cs=multiply(polygon[i],polygon[i+1],polygon[0])/2;
		//�������������ֱ�����øù�ʽ���  
		if(abs(s)<1e-20)  
		{  
			x=x0;y=y0;s+=cs;continue;
		}
		k=cs/s; //���������  
		x=(x+k*x0)/(1+k);
		y=(y+k*y0)/(1+k);
		s += cs;
	}
	tp.x=x;
	tp.y=y;
	return tp;
} 
 
/*��ν͹����ε�ֱ��,��͹���������������������롣������㷨 
����ʱO(n),��һ��������㷨�� ���������һ��͹�����,�Ҷ��� 
���밴˳��˳ʱ�롢��ʱ����ɣ��������롣�����벻��͹����� 
����һ��㼯,��Ҫ������͹���� ��������������Ŷ�,Ȼ�����ÿ 
���ŶԵľ���,ȡ����ߡ�����Ҫ����5��*/ 
void Diameter(Point ch[],int n,double &dia) 
{ 
	int znum=0,i,j,k=1; 
	int zd[MAXV][2]; 
	double tmp; 
	while(amultiply(ch[0],ch[k+1],ch[n-1]) > amultiply(ch[0],ch[k],ch[n-1])-EP)  
	   k++;
	i=0; 
	j=k; 
	while(i<=k && j<n)  
	{    
		zd[znum][0]=i; 
		zd[znum++][1]=j; 
		while(amultiply(ch[i+1],ch[j+1],ch[i]) > amultiply(ch[i+1],ch[j],ch[i]) - EP 
			&& j< n-1)  
		{ 
			zd[znum][0]=i; 
			zd[znum++][1]=j; 
			j++; 
		}
		i++;
	} 
	dia=-1.0; 
	for(i=0;i<znum;i++)  
	{  
		printf("%d %d\n",zd[i][0],zd[i][1]); 
		tmp=dist(ch[zd[i][0]],ch[zd[i][1]]); 
		if(dia<tmp)  
		dia=tmp; 
	} 
} 