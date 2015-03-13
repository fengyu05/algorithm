template<class T> struct coord{
	T** m;
	int r,c,of;
	coord(int r=256,int c=256,int of=128):r(r),c(c),of(of){
		m=new T*[r];
		for(int i=0;i<r;i++)
			m[i]=new T[c];
	}
	~coord(){
		for(int i=0;i<r;i++)
			delete [] m[i];
		delete [] m;
	}
	T& operator()(int x,int y){ return m[x+of][y+of];}
	T operator()(int x,int y) const{ return m[x+of][y+of];}
};

template<class T,int X,int Y=X> struct coord{
	T m[2*X][2*Y];
	T& operator()(int x,int y){ return m[x+X][y+Y];}
	T operator()(int x,int y) const{ return m[x+X][y+Y];}
};