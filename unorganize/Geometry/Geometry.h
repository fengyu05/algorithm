

 
//<二>线段及直线的基本运算 
 
/* 判断点C在线段AB所在的直线l上垂足P的与线段AB的关系  
本函数是根据下面的公式写的,P是点 C到线段AB所在直线的垂足  
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
 
// 求点C到线段AB 所在直线的垂足 P  
Point perpendicular(Point p,LineSeg l)  
{  
	double r=relation(p,l);
	Point tp;
	tp.x=l.s.x+r*(l.e.x-l.s.x);
	tp.y=l.s.y+r*(l.e.y-l.s.y);
	return tp;
}
 
/* 求点p到线段l的最短距离 
返回线段上距该点最近的点np 注意：np是线段l上到点p最近的点,不一定是垂足 */  
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
 
// 求点p到线段l所在直线的距离 
//请注意本函数与上个函数的区别   
double ptoldist(Point p,LineSeg l)  
{  
	return abs(multiply(p,l.e,l.s))/dist(l.s,l.e);
}
 
/* 计算点到折线集的最近距离,并返回最近点.  
注意：调用的是ptolineseg()函数 */  
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
 
/* 判断圆是否在多边形内*/  
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
 
/* 返回两个矢量l1 和l2的夹角的余弦 (-1 ~ 1) 
注意：如果想从余弦求夹角的话,注意反余弦函数的值域是从 0到pi */  
double cosine(LineSeg l1,LineSeg l2)  
{  
	return(((l1.e.x-l1.s.x)*(l2.e.x-l2.s.x)+(l1.e.y-l1.s.y)*(l2.e.y-l2.s.y))
		/(dist(l1.e,l1.s)*dist(l2.e,l2.s)) );
}
 
// 返回线段 l1与l2 之间的夹角  
//单位：弧度 范围(-pi,pi)  
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

 

 
// 如果线段 l1和l2 相交,返回true 且交点由(inter)返回,否则返回false  
bool intersection(LineSeg l1,LineSeg l2,Point &inter)  
{  
	Line ll1,ll2;
	ll1=makeline(l1.s,l1.e);
	ll2=makeline(l2.s,l2.e);
	if(lineintersect(ll1,ll2,inter)) return online(l1,inter);
	else return false;
}
 
//<三> 多边形常用算法模块  
//如果无特别说明,输入多边形顶点要求按逆时针排列  
// 返回多边形面积(signed); 
// 输入顶点按逆时针排列时,返回正值;否则返回负值  
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
// 判断顶点是否按逆时针排列 
// 如果输入顶点按逆时针排列,返回true  
bool isconterclock(int vcnt,Point polygon[])  
{  
	return area_of_polygon(vcnt,polygon)>0;
}
 
/*射线法判断点q与多边形polygon 的位置关系 
要求polygon 为简单多边形,顶点时针排列  
如果点在多边形内：  返回0  
如果点在多边形边上：返回1  
如果点在多边形外：  返回2 */  
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
			c++;  // 相交且不在端点  
 
        if(online(l1,l2.e)&& !online(l1,l2.s) && l2.e.y>l2.e.y) 
			c++;//l2的一个端点在 l1上且该端点是两端点中纵坐标较大的那个 
		if(!online(l1,l2.e)&& online(l1,l2.s) && l2.e.y<l2.e.y) 
			c++;//忽略平行边 
	}
	if(c%2 == 1)  
		return 0;
    else  
		return 2; 
} 
 
//判断点q在凸多边形polygon 内 
// 点q是凸多边形polygon 内[包括边上]时,返回true 
// 注意：多边形polygon 一定要是凸多边形   
bool InsideConvexPolygon(int vcnt,Point polygon[],Point q)  
{  
	Point p;
	LineSeg l;
	int i;
	p.x=0; p.y=0;
	for(i=0;i<vcnt;i++) // 寻找一个肯定在多边形polygon 内的点p：多边形顶点平均值  
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
		/* 点p和点q在边 l 的两侧,说明点q肯定在多边形外 */  
		return false; 
	}
	return true; 
}
 
/*寻找凸包的 graham 扫描法  
PointSet 为输入的点集;  
ch为输出的凸包上的点集,按照逆时针方向排列;
n为PointSet 中的点的数目  
len为输出的凸包上的点的个数 */  
void Graham_scan(Point PointSet[],Point ch[],int n,int &len)  
{  
	int i,j,k=0,top=2;
	Point tmp;
	// 选取PointSet 中y坐标最小的点PointSet[k],如果这样的点有多个,则取最左边的一个  
	for(i=1;i<n;i++)  
		if ( PointSet[i].y<PointSet[k].y || (PointSet[i].y==PointSet[k].y) 
			&& (PointSet[i].x<PointSet[k].x) )  
				k=i;
	tmp=PointSet[0];
	PointSet[0]=PointSet[k];
	PointSet[k]=tmp; // 现在PointSet 中y坐标最小的点在PointSet[0]  
	for (i=1;i<n-1;i++) /* 对顶点按照相对PointSet[0]的极角从小到大进行排序,极角相同  
	的按照距离PointSet[0]从近到远进行排序 */  
	{  
		k=i;
		for (j=i+1;j<n;j++)  
			if ( multiply(PointSet[j],PointSet[k],PointSet[0])>0 ||    // 极角更小     
			  (multiply(PointSet[j],PointSet[k],PointSet[0])==0) &&  /* 极角相等,距离更短  */     
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
 
// 卷包裹法求点集凸壳,参数说明同graham 算法     
void ConvexClosure(Point PointSet[],Point ch[],int n,int &len)  
{  
	int top=0,i,index,first;
	double curmax,curcos,curdis;
	Point tmp;
	LineSeg l1,l2;
	bool use[MAXV];
	tmp=PointSet[0];
	index=0;
	// 选取y最小点,如果多于一个,则选取最左点  
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
		// 选取与最后一条确定边夹角最小的点,即余弦值最大者  
		for(i=0;i<n;i++)  
		{  
			if(use[i])continue;
			l2.e=PointSet[i];
			curcos=cosine(l1,l2); // 根据cos值求夹角余弦,范围在 （-1 -- 1 ）  
			if(curcos>curmax || fabs(curcos-curmax)<1e-6 && dist(l2.s,l2.e)>curdis)  
			{  
				curmax=curcos;
				index=i;
				curdis=dist(l2.s,l2.e);
			} 
		}
		use[first]=false;   //清空第first 个顶点标志,使最后能形成封闭的hull  
		use[index]=true;
		ch[top++]=PointSet[index];
		l1.s=ch[top-2];
		l1.e=ch[top-1];
		l2.s=ch[top-1];
	}
	len=top-1;
}
// 求凸多边形的重心,要求输入多边形按逆时针排序  
Point gravitycenter(int vcnt,Point polygon[])  
{  
	Point tp;
	double x,y,s,x0,y0,cs,k;
	x=0;y=0;s=0;
	for(int i=1;i<vcnt-1;i++)  
	{  
		x0=(polygon[0].x+polygon[i].x+polygon[i+1].x)/3;
		y0=(polygon[0].y+polygon[i].y+polygon[i+1].y)/3; //求当前三角形的重心  
		cs=multiply(polygon[i],polygon[i+1],polygon[0])/2;
		//三角形面积可以直接利用该公式求解  
		if(abs(s)<1e-20)  
		{  
			x=x0;y=y0;s+=cs;continue;
		}
		k=cs/s; //求面积比例  
		x=(x+k*x0)/(1+k);
		y=(y+k*y0)/(1+k);
		s += cs;
	}
	tp.x=x;
	tp.y=y;
	return tp;
} 
 
/*所谓凸多边形的直径,即凸多边形任两个顶点的最大距离。下面的算法 
仅耗时O(n),是一个优秀的算法。 输入必须是一个凸多边形,且顶点 
必须按顺序（顺时针、逆时针均可）依次输入。若输入不是凸多边形 
而是一般点集,则要先求其凸包。 就是先求出所有跖对,然后求出每 
个跖对的距离,取最大者。点数要多于5个*/ 
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