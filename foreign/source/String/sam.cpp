int n, K, flag, nodecnt;
char str[maxn];
int siz[maxn], Ws[maxn], Q[maxn];ll sum[maxn];
struct Node{
    int nx[26], len, root;
}T[maxn];
inline void Init(){
    nodecnt = 0;
    T[0].root = -1, T[0].len = 0;
}
inline int Extend(int p, int c){
    int np = ++nodecnt;
    T[np].len = T[p].len + 1, siz[np] = 1;
    for(;p != -1 && !T[p].nx[c];p = T[p].root)T[p].nx[c] = np;
    if(p == -1)T[np].root = 0;
    else{
        int q = T[p].nx[c];
        if(T[q].len == T[p].len + 1)T[np].root = q;
        else{
            int nq = ++nodecnt;
            T[nq] = T[q];T[nq].len = T[p].len + 1;
            for(;p != -1 && T[p].nx[c] == q;p = T[p].root)T[p].nx[c] = nq;
            T[q].root = T[np].root = nq;
        }
    }
    return np;
}
void Dfs(int x){
    if(K <= siz[x])return;
    K -= siz[x];
    for(int c = 0;c < 26;++c){
        if(T[x].nx[c]){
            if(K <= sum[T[x].nx[c]]){
                putchar('a' + c);
                Dfs(T[x].nx[c]);
                break;
            }
            else K -= sum[T[x].nx[c]];
        }
    }
}
int main(){
    scanf("%s", str);n = strlen(str);
    scanf("%d%d", &flag, &K);
    Init();
    for(int i = 0, last = 0;i < n;++i)last = Extend(last, str[i] - 'a');
    for(int i = 1;i <= nodecnt;++i)Ws[T[i].len]++;
    for(int i = 1;i <= n;++i)Ws[i] += Ws[i - 1];
    for(int i = nodecnt;i > 0;--i)Q[Ws[T[i].len]--] = i;
    for(int i = nodecnt, x;i > 0;--i){
        x = Q[i];
        if(!flag)siz[x] = 1;
        else siz[T[x].root] += siz[x];
    }
    siz[0] = 0;
    for(int i = nodecnt, x;i >= 0;--i){
        x = Q[i];
        sum[x] = siz[x];
        for(int c = 0;c < 26;++c){
            if(T[x].nx[c])sum[x] += sum[T[x].nx[c]];
        }
    }
    if(sum[0] < K)puts("-1");
    else Dfs(0);
    return 0;
}
