bool Palindromes(const char s[],int len)
{
    for(int i=0;i<len/2;i++)
        if(s[i] != s[len-i-1])
            return false;
    return true;
}

bool Symmetry (int n)//�жϻ�������
{
	int i,temp;
	i=n; temp=0;
	while(i) //���ó��ֳ�������,�������ߵ�λ����
	{
		temp=temp*10+i%10;
		i/=10;
	}
	return(temp==n);
}
