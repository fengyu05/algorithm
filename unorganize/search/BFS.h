struct State{
	State():{}
	operator int() const{ return ;}
};
bool operator==(State& a,State &b){	return ;}
char close[N];
int BFS(State S,State T){
	deque<State> open;
	memset(close,-1,sizeof(close));
	open.push_back(S);
	close[S]=0;
	while(open.size()){
		State cur=open.front(),next;
		open.pop_front();
		if(cur==T) return close[cur];		
		//for each state can reach by cur 
		{
			//get new state	to next;
			if(close[next]==-1){//判重
				close[next]=close[cur]+1;	
				open.push_back(next);
			}
		}		
	}
	return -1;
}

//双向BFS
//正反交替搜索

//周界搜索 perimeter search
//先反向搜索一下，存储结点。在正向搜索
//周界表示 hash表
//正向搜索策略 BFS ID
//反向深度 应为 总深度一半略少