void Init(){nodecnt = 0;T[0].root = -1, T[0].len = 0;}
int Extend(int p, int c){
    int np = ++nodecnt;T[np].len = T[p].len + 1, siz[np] = 1;
    for(;p != -1 && !T[p].nx[c];p = T[p].root)T[p].nx[c] = np;
    if(p == -1)T[p].root = 0;
    else{
        int q = T[p].nx[c];
        if(T[q].len == T[p].len + 1)T[np].root = q;
        else{
            int nq = ++nodecnt;T[nq] = T[q];T[nq].len = T[p].len + 1;
            for(;p != -1 && T[p].nx[c] == q;p = T[p].root)T[p].nx[c] = nq;
            T[q].root = T[np].root = nq;
        }
    }
    return np;
}
int main(){Init();
    for(int i = 0, last = 0;i < n;++i) last = Extend(last, str[i] - 'a');
    for(int i = 1;i <= nodecnt;++i) Ws[T[i].len]++;
    for(int i = 1;i <= n;++i) Ws[i] += Ws[i - 1];
    for(int i = nodecnt;i > 0;--i) Q[Ws[T[i].len]--] = i;
    for(int i = nodecnt, x;i > 0;--i){
        x = Q[i]; //siz表示求right集合的大小。
        if(!flag)siz[x] = 1;else siz[T[x].root] += siz[x];
    }
}

