可以不使用iomanip的，
cout.precision()设置小数点后精确度，
cout.width()设置宽度，
cout.setf()设置显示格式，比如
cout.setf(ios::left)左对齐 
cout.setf(ios::showpoint)不管是否有小数位，显示小数点 
cout.fill();不足宽度则填充，如cout.fill('0');

仅仅cout.precision(6)和cout.setf(ios::showpoint)时，不知何原因如果为0只显示到小
数点后5位，所以为了在最后加个0,要加上其它3项

补充（部分是iomanip里的）：
long flags( ) const 返回当前的格式标志。
long flays(long newflag) 设置格式标志为newflag，返回旧的格式标志。
long setf(long bits) 设置指定的格式标志位，返回旧的格式标志。
long setf(long bits,long field)将field指定的格式标志位置为bits，返回旧的格式标
志  
long unsetf(long bits) 清除bits指定的格式标志位，返回旧的格式标志。
long fill(char c) 设置填充字符，缺省条件下是空格。
char fill( ) 返回当前填充字符。
int precision(int val) 设置精确度为val，控制输出浮点数的有效位，返回旧值。
int precision( ) 返回旧的精确度值。
int width(int val) 设置显示数据的宽度(域宽),返回旧的域宽。
int width( )只返回当前域宽，缺省宽度为0。这时插入操作能按表示数据的最小宽度显示
数据
dec 十进制的输入输出
hex 十六进制的输入输出
oct 八进制的输入输出
ws 提取空白字符  //cin >> ws  跳过空格
flush 刷新流
resetiosflags(long) 请除特定的格式标志位
setiosflags(long) 设置特定的格式标志位
setfill(char) 设置填充字符
setprecision(int) 设置输出浮点数的精确度
setw(int) 设置域宽格式变量