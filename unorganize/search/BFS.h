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
			if(close[next]==-1){//����
				close[next]=close[cur]+1;	
				open.push_back(next);
			}
		}		
	}
	return -1;
}

//˫��BFS
//������������

//�ܽ����� perimeter search
//�ȷ�������һ�£��洢��㡣����������
//�ܽ��ʾ hash��
//������������ BFS ID
//������� ӦΪ �����һ������