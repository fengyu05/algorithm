#include <stdio.h>

/*  
 �� val=min( (|xi-x|+|yi-y|+|zi-z|)/pi )
 
 ����val
 �ж��Ƿ�����|xi-x|+|yi-y|+|zi-z|<=pi*val i=[1..n]
 
 ���ж����в���ʽ�Ƿ��н�
 a*x+b*y+c*z<=min(pi*val+a*xi+b*yi+c*zi) i=[1..n]
 st. a,b,c=[1,-1]
 
 �� best[a][b][c]=min(pi*val+a*xi+b*yi+c*zi) i=[1..n]
 ���ж��Ƿ����㣺0=a*x+b*y+c*z + -a*x-b*x-c*x <=best[a][b][c]+best[-a][-b][-c]
*/
int n;
int x[1000], y[1000], z[1000], p[1000];
int test (double pow) {

    double best[2][2][2];
    int a, b, c;
    
    for (a = 0; a < 2; a ++)
        for (b = 0; b < 2; b ++)
            for (c = 0; c < 2; c ++)
                best[a][b][c] = 1e20;
    
    for (int i = 0; i < n; i ++)
        for (a = 0; a < 2; a ++)
            for (b = 0; b < 2; b ++)
                for (c = 0; c < 2; c ++){
					double tmp=(a?x[i]:-x[i]) + (b?y[i]:-y[i]) + (c?z[i]:-z[i])+ pow*p[i];
					if(best[a][b][c]>tmp) best[a][b][c]=tmp;
				}
    for (a = 0; a < 2; a ++)
        for (b = 0; b < 2; b ++)
            for (c = 0; c < 2; c ++)
                if (best[a][b][c] + best[!a][!b][!c] < 0)
                    return 0;
    return 1;
}

int main () {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
    int t, i, ct = 0;
    
    for (scanf("%d", &t); t > 0; t --) {
        scanf("%d", &n);        
        for (i = 0; i < n; i ++)
            scanf("%d%d%d%d", x + i, y + i, z + i, p + i);
        
        double l, m, r;
        
        l = 0;
        r = 1e20;
        for (int ii = 0; ii < 100; ii ++) {
            m = (l + r) / 2;            
            if (test(m))
                r = m;
            else
                l = m;
            }        
			printf("Case #%d: %.6lf\n", ++ ct, (l + r) / 2);
        }
    
    return 0;
}
