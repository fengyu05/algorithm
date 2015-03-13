#include <cstdio>
#include <ctime>


void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLK_TCK ;
  while (clock() < endwait) {}
}


   int ss = clock(); 
   printf("%f\n", (double)(clock()-ss)/1000); 