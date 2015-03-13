
#include<cstdio>
int main()
{
    //for int
    int i=30122121;
    long i2=309095024l;
    short i3=30;
    unsigned i4=2123453;
    printf("%d,%o,%x,%X,%ld,%hd,%u\n",i,i,i,i,i2,i3,i4);//如果是：%l,%h，则输不出结果
    printf("%d,%ld\n",i,i2);//试验不出%ld和%d之间的差别，因为long是4bytes
    printf("%hd,%hd\n\n\n",i,i3);//试验了%hd和%d之间的差别，因为short是2bytes


    //for string and char
    char ch1='d';
    unsigned char ch2=160;
    char *str="Hello everyone!";
    printf("%c,%u,%s\n\n\n",ch1,ch2,str);//unsigned char超过128的没有字符对应

   
    //for float and double,unsigned and signed can not be used with double and float
    float fl=2.566545445F;//or 2.566545445f
    double dl=265.5651445;
    long double dl2=2.5654441454;

    //%g没有e格式，默认6位包括小数点前面的数,
    //%f没有e格式，默认6位仅只小数点后面包含6位
    //%e采用e格式，默认6位为转化后的小数点后面的6位
    printf("%f,%e,%g,%.7f\n",fl,dl,dl,dl);
    printf("%f,%E,%G,%f\n",fl,dl,dl,dl);//%F is wrong
    printf("%.8f,%.10e\n",fl,dl);
    printf("%.8e,%.10f\n\n\n",fl,dl);

    //for point
    int *iP=&i;
    char *iP1=new char;
    void *iP2;//dangerous!
    printf("%p,%p,%p\n\n\n",iP,iP1,iP2);
   
    //其他知识：负号，表示左对齐（默认是右对齐）；%6.3，6表示宽度，3表示精度

    char *s="Hello world!";
    printf(":%s: \n:%10s: \n:%.10s: \n:%-10s: \n:%.15s: \n:%-15s: \n:%15.10s:\n:%-15.10s:\n\n\n",
        s,s,s,s,s,s,s,s);
    double ddd=563.908556444;
    printf(":%g: \n:%10g: \n:%.10g: \n:%-10g: \n:%.15g: \n:%-15g: \n:%15.10g:\n:%-15.10g:\n\n\n",
        ddd,ddd,ddd,ddd,ddd,ddd,ddd,ddd);

    //还有一个特殊的格式%*.* ,这两个星号的值分别由第二个和第三个参数的值指定

    printf("%.*s \n", 8, "abcdefgggggg");
    printf("%*.*f   \n", 3,3, 1.25456f);
 
    return 0;
}