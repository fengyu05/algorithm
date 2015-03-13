/*
 1119 Start Up the Startup
*/
#pragma warning(disable: 4786)

#include <iostream>
#include <string>
#include <map>
#include <cmath>

using namespace std;
char str[256],buf[256];
void filter()
{
	int j=0;	
 	for(int i=0;buf[i];i++){
		if(isalpha(buf[i]))
		    str[j++]=tolower(buf[i]);
		else if(isdigit(buf[i]))
			str[j++]=buf[i];
	}
	str[j]=0;
}
int main()
{
		map<string,pair<int,int> > mm;
		map<string,pair<int,int> >::iterator mit;
		while(scanf("%s",buf),strcmp(buf,"----------")!=0){
			filter();
			if(str[0]==0) continue;
			mit=mm.find(string(str));
			if(mit==mm.end()){
				mm.insert(make_pair(string(str),make_pair(1,0)));
			}
			else (mit->second.first)++;
		}

		while(scanf("%s",buf),strcmp(buf,"----------")!=0){
			for(mit=mm.begin();mit!=mm.end();++mit)	mit->second.second=0;

			filter();
			mit=mm.find(string(str));
			if(mit!=mm.end())(mit->second.second)++;

			while(scanf("%s",buf),strcmp(buf,"----------")!=0) {
				filter();
				if(str[0]==0) continue;
				mit=mm.find(string(str));
				if(mit!=mm.end())(mit->second.second)++;
			}
			double re=0;
			for(mit=mm.begin();mit!=mm.end();++mit){
				re+=sqrt((double)mit->second.first*mit->second.second);
			}
			printf("%.2lf\n",re);
		}
	
}