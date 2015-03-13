
#include<cstdio>
int main()
{
    //for int
    int i=30122121;
    long i2=309095024l;
    short i3=30;
    unsigned i4=2123453;
    printf("%d,%o,%x,%X,%ld,%hd,%u\n",i,i,i,i,i2,i3,i4);//����ǣ�%l,%h�����䲻�����
    printf("%d,%ld\n",i,i2);//���鲻��%ld��%d֮��Ĳ����Ϊlong��4bytes
    printf("%hd,%hd\n\n\n",i,i3);//������%hd��%d֮��Ĳ����Ϊshort��2bytes


    //for string and char
    char ch1='d';
    unsigned char ch2=160;
    char *str="Hello everyone!";
    printf("%c,%u,%s\n\n\n",ch1,ch2,str);//unsigned char����128��û���ַ���Ӧ

   
    //for float and double,unsigned and signed can not be used with double and float
    float fl=2.566545445F;//or 2.566545445f
    double dl=265.5651445;
    long double dl2=2.5654441454;

    //%gû��e��ʽ��Ĭ��6λ����С����ǰ�����,
    //%fû��e��ʽ��Ĭ��6λ��ֻС����������6λ
    //%e����e��ʽ��Ĭ��6λΪת�����С��������6λ
    printf("%f,%e,%g,%.7f\n",fl,dl,dl,dl);
    printf("%f,%E,%G,%f\n",fl,dl,dl,dl);//%F is wrong
    printf("%.8f,%.10e\n",fl,dl);
    printf("%.8e,%.10f\n\n\n",fl,dl);

    //for point
    int *iP=&i;
    char *iP1=new char;
    void *iP2;//dangerous!
    printf("%p,%p,%p\n\n\n",iP,iP1,iP2);
   
    //����֪ʶ�����ţ���ʾ����루Ĭ�����Ҷ��룩��%6.3��6��ʾ��ȣ�3��ʾ����

    char *s="Hello world!";
    printf(":%s: \n:%10s: \n:%.10s: \n:%-10s: \n:%.15s: \n:%-15s: \n:%15.10s:\n:%-15.10s:\n\n\n",
        s,s,s,s,s,s,s,s);
    double ddd=563.908556444;
    printf(":%g: \n:%10g: \n:%.10g: \n:%-10g: \n:%.15g: \n:%-15g: \n:%15.10g:\n:%-15.10g:\n\n\n",
        ddd,ddd,ddd,ddd,ddd,ddd,ddd,ddd);

    //����һ������ĸ�ʽ%*.* ,�������Ǻŵ�ֵ�ֱ��ɵڶ����͵�����������ֵָ��

    printf("%.*s \n", 8, "abcdefgggggg");
    printf("%*.*f   \n", 3,3, 1.25456f);
 
    return 0;
}