// �������ϸ�������е��������������մ�
int increasing_order_cnt(int p[],int n){
       int seqs[N]={0};
       int cnt = 0;
       for (int i = 0; i < n; ++i) {
               seqs[i] = 1;
               for (int j = 0; j < i; ++j)
                       if (p[j] < p[i]) seqs[i] += seqs[j];
               cnt += seqs[i];
       }
       return cnt;
}