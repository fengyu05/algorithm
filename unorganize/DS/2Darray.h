//
template<typename T>  
void make2Darray(T **&x,int rows,int cols){
	x=new T*[rows];  
	T *p =new T[rows*cols];  
	for(int i=0;i<rows;i++)  
		x[i]=p+i*cols;
}
template<typename T>
void destroy2Darray(const T* const* x){  
	delete [] x[0];
	delete [] x;  
}
//-------------------------------
template<class T> struct Array{
	T* body;
	int row,col,curR;
	Array(int r,int c){
		body=new T[r*c];
		row=r,col=c;
	}
	~Array(){delete [] body;}
	T& operator[](int j){
		if(curR<0||curR>=col||j<0||j>=col)
			cerr<<"Out of bound!\n";
		return body[curR*col+j];
	}
};
template<class T> struct Array2D{
	Array<T> body;
	Array<T>& operator[](int i){
		body.curR=i;
		return body;
	}
	Array2D(int r,int c):body(r,c){}
};