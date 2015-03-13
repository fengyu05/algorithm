// 1st 2nd 3rd ..th ex: ..11th ..12th ..13th
char suf[4][2]={"th","st","nd","rd"};
int GetSuffix(int num)
{
	if(num%100>=11&&n%100<=13) return 0;
	if(!(n%10>=1&&n%10<=3)) return 0;
	else return n%10;
}

// name search
char name[200][48];
int cnt;
char str[48];
int dex(){
	int i;
	for(i=0;i<cnt;i++)
		if(strcmp(name[i],str)==0)
			return i;
	strcpy(name[i],str);
	return i;
}
//string sort

char name[1000000][40];
char  pos[1000000];
bool cmp(int a,int b){
	return lexicographical_compare(name[a],name[a]+strlen(name[a]),
						name[b],name[b]+strlen(name[b]));
}

sort(pos,pos+n,cmp);
for(i=0;i<n;i++){
	puts(name[pos[i]]);
}
class cmp
{
public:
	bool operator()(int a,int b){
		return lexicographical_compare(name[a],name[a]+strlen(name[a]),
							name[b],name[b]+strlen(name[b]));
	}
};







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