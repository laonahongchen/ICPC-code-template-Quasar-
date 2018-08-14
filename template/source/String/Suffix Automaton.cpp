### $Suffix \space Automaton$
- $right$集合的大小就是该状态表示所有的子串在整个字符串的出现次数。
    $size_{T_x.fail} += size_x$
- 两个串的最长公共子串:
建出A串的后缀自动机，然后B串在后缀自动机上跑，如果能匹配就继续，不能的话一直跳fail直到能匹配或跳到根。
- 本质不同的子串的个数:
 - 从起点沿着转移边到达某个状态都对应一个不同的子串,问题转化成统计状态图上的路径条数，在自动机上Dfs或者按状态长度基数排序：$f_x=\sum f_{T_x.ch_c}+1$。
 - 一个状态代表的串的长度是一个区间：$\sum (T_x.len ? T_{T_x.root}.len)$。
```
BZOJ 3998 [TJOI2015]弦论
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
    if(p == -1)T[p].root = 0;
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
```
