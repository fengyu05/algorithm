class Dictionary{
public:
	map<string,int> mm;
	typedef map<string,int>::iterator mit;
	int cnt;
	Dictionary(){cnt=0;}
	int word(const string& s){
		mit pos=mm.find(s);
		if(pos==mm.end()){
			mm.insert(make_pair(s,cnt++));
			return cnt-1;
		}else return pos->second;		
	}
};
// init cnt=0;
char name[22][11];
int cnt;
int getId(char str[])
{
	for(int i = 1; i < cnt; i++)
	{
		if(strcmp(str,name[i])==0)
			return i;
	}
	strcpy(name[cnt],str);
	return cnt++;
}