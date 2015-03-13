/*
    最大团=最大完全子图
最大独立集=最大不相连子图
G图的最大团=G的补图的最大独立集
*/
// adj-list version
int list[N][N] ,adj[N][N] , s [N] , deg[N] , behide [N];
int found ,n,curmax, curobj ;
void sortdeg()
{
	for(int j ,k, l ,i=1;i<=n; i++) {
		for(k=i,j=i+1;j<=n; j++) if (deg[j]<deg[k])
			k=j;
			if (k!=i ){
				swap(deg[i] , deg[k]);
				for( l=1;l<=n; l++) swap(adj[i][l] ,adj[k][l]);
				for( l=1;l<=n; l++) swap(adj[l][i] ,adj[l][k]);
			}
	}
}
void dfs(int d)
{
	if(d-1>curmax ){
		found=1; return;
	}
	int i , j ;
	for( i=1;i<list [d-1][0]-curmax+d; i++)
		if (! found && d+behide [ list [d-1][ i]+1]>curmax &&
		(list[d-1][0]==i || d+behide [ list [d-1][ i+1]]>curmax )) {
			for( j=i+1, list [d][0]=0; j<=list [d-1][0]; j++)
				if ( adj[ list [d-1][ j ]][ list [d-1][ i ]] )
					list [d][++ list [d][0]]= list [d-1][ j ];
		if ( list[d][0]==0 || d + behide [ list [d][1]] >curmax)
			dfs(d+1);
	}
}
void solve ()
{
	sortdeg();
	behide[n+1]=0;
	behide[n]=1;
	for(int j, i=n-1;i >0;i--) {
		curmax=behide[i +1];
		found=list[1][0]=0;
		for(j=i+1;j<=n; j++) if(adj[j][i])
			list[1][ ++list[1][0] ] = j ;
		dfs(2);
		behide[i]=curmax+found;
	}
	cout<<behide[1]<<endl;
}

// matrix version
int n,maxc,c[50];
bool mat[50][50] , found ;
void MaxClique(bool flag[50], int size )
{
	int i , j ,k=0;
	bool mark[50];
	for(i=0;i<n; i++) if(!flag[i]) k++;
	if (!k){
		if(size>maxc)
			maxc=size,found=true;
		return;
	}
	for( i=0;i<n; i++) if (!flag[i]){
		if ( size+k<=maxc) return;
		if ( size+c[i]<=maxc) return;
		flag[i]=1,k--;
		for( j=0;j<n; j++)
			mark[j]=flag[j];
		for( j=0;j<n; j++) if(!mat[ i ][ j ])
			mark[j]=1;
		MaxClique(mark, size+1);
		if(found) return;
	}
}
void MaxClique(){
	int i,j;
	maxc=0;
	bool flag[50];
	for(i=n-1;i>=0;i--){
		for( j=0;j<=i; j++) flag [j]=1;
		for( j=i+1;j<=n; j++){
			if(mat[i][j]) flag[j]=0;
			else flag[j]=1;
		}
		found=false;
		MaxClique(flag ,1) ;
		c[i]=maxc;
	}
}