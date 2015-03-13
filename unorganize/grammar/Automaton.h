// Author: Peter Schaeffer

#include <stdio.h>
#include <string.h>

#define MEMO 1

#define MAXSIZE 5000
#define MAXDEPTH MAXSIZE

#define SET 0x01
#define LISTE 0x02
#define LIST 0x04
#define LISTSEP 0x08

FILE *in;
int n;
char s[MAXSIZE+1];

#if MEMO
unsigned char memo[MAXSIZE+1][MAXDEPTH+1];
#endif


int list(char *c, int depth);
int set(char *c, int depth);

int listsep(char *c, int depth)
{
#if MEMO
  if (memo[c-s][depth]&LISTSEP) return 0;
  memo[c-s][depth]|=LISTSEP;
#endif
  if (!depth)
    if (!*c)
      return 1;
    else
      return 0;
  if (*c==',')
    return list(c+1, depth);
  if (*c=='}')
    return listsep(c+1, depth-1);
  return 0;
}

int list(char *c, int depth)
{
#if MEMO
  if (memo[c-s][depth]&LIST) return 0;
  memo[c-s][depth]|=LIST;
#endif
  if (*c=='{')
    {
      if (listsep(c+1, depth))
        return 1;
      return set(c, depth);
    }
  else if (*c=='}')
    return listsep(c+1, depth);
  else if (*c==',')
    return listsep(c+1, depth);
  return 0;
}

int liste(char *c, int depth)
{
#if MEMO
  if (memo[c-s][depth]&LISTE) return 0;
  memo[c-s][depth]|=LISTE;
#endif
  if ((*c=='}') && (listsep(c+1, depth-1)))
    return 1;
  return list(c, depth);
}

int set(char *c, int depth)
{
#if MEMO
  if (memo[c-s][depth]&SET) return 0;
  memo[c-s][depth]|=SET;
#endif
  if (*c!='{') return 0;
  return liste(c+1, depth+1);
}

int main()
{
  in=fopen("fool.in", "r");
  fscanf(in, " %d ", &n);
  for(int w=1; w<=n; w++)
    {
      fscanf(in, " %s ", s);
#if MEMO
      int length=strlen(s)+1;
      int ms=length;
      int md=(length>MAXDEPTH)?(MAXDEPTH):(length);
        for(int i=0; i<ms; i++)
          for(int j=0; j<md; j++)
	memo[i][j]=0;
#endif
      printf("Word #%d:%s Set\n", w, ((set(s, 0))?(""):(" No")));
    }
  return 0;
}