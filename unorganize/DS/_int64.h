#ifdef WIN32
typedef signed __int64 i64;
typedef unsigned __int64 u64;

istream& operator>>(istream& s, i64& d)
{                                      
    char b[30];                        
        s>>b;                              
        sscanf(b, "%I64d", &d);               
        return s;                          
}                                      
ostream& operator<<(ostream& s, i64 d)
{                                      
        char b[30];                        
        sprintf(b,"%I64d",d);                 
        s<<b;                              
        return s;                          
} 

#else
typedef signed long long i64;
typedef unsigned long long u64;
#endif