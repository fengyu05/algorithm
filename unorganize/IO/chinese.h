void go(char str[]){
	char tmp[3]; tmp[2]=0;
	for(int i=0;str[i];i++){
		tmp[i%2]=str[i];
		if(i%2==1) printf("%s",tmp);
	}
}