bool Palindromes(const char s[],int len)
{
    for(int i=0;i<len/2;i++)
        if(s[i] != s[len-i-1])
            return false;
    return true;
}

bool Symmetry (int n)//判断回文数字
{
	int i,temp;
	i=n; temp=0;
	while(i) //不用出现长度问题,将数按高低位掉换
	{
		temp=temp*10+i%10;
		i/=10;
	}
	return(temp==n);
}
