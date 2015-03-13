/*
1)
abs(x) return int abs(-0.3)=0
use fabs on double

2)
sqrt(3) maybe CE
ambiguous call to overloaded function
use sqrt(3.0) instead

3)
RE时巧用 try..catch
try{
}catch(char e){ ..}

4)用0x7fffffff作为INF时，
切勿对其使用+，改为相对小一些的值

5)深搜索时注意选择深度较小的状态表示方法

6)上溢检测
a+=x;
if(a<0){
 a=INF;
 or do sth;
}

7)  make sure no -0.0000 happen

