// use BFS
bool mat[N][N];
int BtoG[N], GtoB[N];
int Bipartite(int B,int G){    
    int queue[N], prev[N], front, rear;
	int i, j, x, n=0;
    memset(BtoG,-1,B*4);
	memset(GtoB,-1,G*4);
    for( i = 0; i < B; i++ ) {
        for( j = 0; j < G; j++ ) prev[j] = -2;
        front = rear = 0;
        for( j = 0; j < G; j++ )
			if( mat[i][j] )
			{
				prev[j] = -1;
				queue[rear++] = j;
			}
        while( front < rear ){
            x = queue[front];
            if( GtoB[x] == -1 ) break;
            front++;
            for( j = 0; j < G; j++ )
				if( prev[j] == -2 && mat[GtoB[x]][j] )
				{
					prev[j] = x;
					queue[rear++] = j;
				}
        }
        if( front == rear ) continue;
        while( prev[x] > -1 )
		{
            BtoG[GtoB[prev[x]]] = x;
            GtoB[x] = GtoB[prev[x]];
            x = prev[x];
        }
        GtoB[x] = i, BtoG[i] = x;
        n++;
    }
    return n;
}