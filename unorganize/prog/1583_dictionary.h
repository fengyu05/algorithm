#pragma warning(disable: 4786)

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Dictionary{
public:
	map<string,int> mm;
	typedef map<string,int>::iterator mit;
	#define N 1024
	int cnt,index[N];
	Dictionary(){cnt=0;memset(index,0,sizeof(index));}
	int word(const string& s){
		mit pos=mm.find(s);
		if(pos==mm.end()){
			mm.insert(make_pair(s,cnt++));
			return cnt-1;
		}else return pos->second;		
	}

	int list[N],l_cnt;
	void findmost(){
		int max=0,l_cnt=0;
		mit pos;
		for(pos=mm.begin();pos!=mm.end();++pos){
			int i=pos->second;
			if(index[i]>max) max=index[i],list[(l_cnt=0)++]=i;
			else if(index[i]==max) list[l_cnt++]=i;
		}
		cout<<max<<" occurrences\n";
		for(pos=mm.begin();pos!=mm.end();++pos){
			for(int i=0;i<l_cnt;i++){
				if(pos->second==list[i]){
					cout<<pos->first<<endl;
					break;
				}
			}
		}
	}
};
void main()
{
#ifndef ONLINE_JUDGE
  	freopen("t.in", "r", stdin);
#endif
	Dictionary dic;
	const string delims(" \t,.;`\'\"()/:-");
	string line,tmp;

	while(getline(cin,line)){
		string::size_type begIdx, endIdx;
		begIdx = line.find_first_not_of(delims);
		while (begIdx != string::npos) {
			endIdx = line.find_first_of (delims, begIdx);
			tmp=line.substr(begIdx,endIdx-begIdx);
			if(tmp[0]>='A'&&tmp[0]<='Z') tmp[0]=tmp[0]-'A'+'a';
			int pos=dic.word(tmp);
			dic.index[pos]++;
			begIdx = line.find_first_not_of (delims, endIdx);
		}
	}
	dic.findmost();
	
}