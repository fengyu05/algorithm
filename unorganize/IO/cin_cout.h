���Բ�ʹ��iomanip�ģ�
cout.precision()����С�����ȷ�ȣ�
cout.width()���ÿ�ȣ�
cout.setf()������ʾ��ʽ������
cout.setf(ios::left)����� 
cout.setf(ios::showpoint)�����Ƿ���С��λ����ʾС���� 
cout.fill();����������䣬��cout.fill('0');

����cout.precision(6)��cout.setf(ios::showpoint)ʱ����֪��ԭ�����Ϊ0ֻ��ʾ��С
�����5λ������Ϊ�������Ӹ�0,Ҫ��������3��

���䣨������iomanip��ģ���
long flags( ) const ���ص�ǰ�ĸ�ʽ��־��
long flays(long newflag) ���ø�ʽ��־Ϊnewflag�����ؾɵĸ�ʽ��־��
long setf(long bits) ����ָ���ĸ�ʽ��־λ�����ؾɵĸ�ʽ��־��
long setf(long bits,long field)��fieldָ���ĸ�ʽ��־λ��Ϊbits�����ؾɵĸ�ʽ��
־  
long unsetf(long bits) ���bitsָ���ĸ�ʽ��־λ�����ؾɵĸ�ʽ��־��
long fill(char c) ��������ַ���ȱʡ�������ǿո�
char fill( ) ���ص�ǰ����ַ���
int precision(int val) ���þ�ȷ��Ϊval�������������������Чλ�����ؾ�ֵ��
int precision( ) ���ؾɵľ�ȷ��ֵ��
int width(int val) ������ʾ���ݵĿ��(���),���ؾɵ����
int width( )ֻ���ص�ǰ���ȱʡ���Ϊ0����ʱ��������ܰ���ʾ���ݵ���С�����ʾ
����
dec ʮ���Ƶ��������
hex ʮ�����Ƶ��������
oct �˽��Ƶ��������
ws ��ȡ�հ��ַ�  //cin >> ws  �����ո�
flush ˢ����
resetiosflags(long) ����ض��ĸ�ʽ��־λ
setiosflags(long) �����ض��ĸ�ʽ��־λ
setfill(char) ��������ַ�
setprecision(int) ��������������ľ�ȷ��
setw(int) ��������ʽ����