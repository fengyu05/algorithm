// ¶Á×Ö·û´®Á÷
#include<sstream>
gets(str);
stringstream ss;
ss.str(str);
while(ss>>x>>y){}

string s=buf;
stringstream ss(s);
int i=0;
while(ss>>F[i++]);

// exception handle
try{}
catch(exception){}


//  Extract word
	const string delims(" \t,.;\'\"()/:-");
	string line,tmp;
	
	while(getline(cin,line)){
		string::size_type begIdx, endIdx;
		begIdx = line.find_first_not_of(delims);
		while (begIdx != string::npos) {
			endIdx = line.find_first_of (delims, begIdx);
			tmp=line.substr(begIdx,endIdx-begIdx);
			cout<<tmp<<endl;
			begIdx = line.find_first_not_of (delims, endIdx);
		}
	}