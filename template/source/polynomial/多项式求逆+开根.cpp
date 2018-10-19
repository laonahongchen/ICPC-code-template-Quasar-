//bzoj 小朋友与二叉树
const int mod = 998244353;
const int phi = 998244352;
const int inv2 = 499122177;
const int maxn = (1 << 18) + 5;
const int G = 3;
int rev[maxn], Tmp[maxn], bi[maxn], f[maxn], g[maxn];
void NTT(int *a, int n, int type){
    int i, j, k, w, wn, pa, pb, K = 0;
    for(K = 0;(1 << K) < n;++K);--K;
    for(int i = 1;i < n;++i){
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << K);
        if(i > rev[i])swap(a[i], a[rev[i]]);
    }
    for(k = 2;k <= n;k <<= 1){
        wn = Pow(G, (type * phi / k % phi + phi) % phi, mod);
        for(j = 0;j < n;j += k){
            w = 1;
            for(i = 0;i < (k >> 1);++i, w = 1LL * w * wn % mod){
                pa = a[i + j];
                pb = 1LL * w * a[i + j + (k >> 1)] % mod;
                a[i + j] = (pa + pb) % mod;
                a[i + j + (k >> 1)] = (pa - pb) % mod;
            }
        }
    }
    if(type == -1){
        int inv = Pow(n, phi - 1, mod);
        for(int i = 0;i < n;++i)a[i] = 1LL * a[i] * inv % mod;
    }
}
void Inv(int *a, int *b, int n){
    if(n == 1){
        b[0] = Pow(a[0], phi - 1, mod);
        return;
    }
    Inv(a, b, n >> 1);
    for(int i = 0;i < n;++i)Tmp[i] = a[i];
    for(int i = n;i < (n << 1);++i)Tmp[i] = 0;
    NTT(Tmp, n << 1, 1);
    NTT(b, n << 1, 1);
    for(int i = 0;i < (n << 1);++i){
        b[i] = 1LL * b[i] * (2 - 1LL * b[i] * Tmp[i] % mod) % mod;
    }
    NTT(b, n << 1, -1);
    for(int i = n;i < (n << 1);++i)b[i] = 0;
}
  
inline void Sqrt(int *a, int *b, int n){
    if(n == 1){
        b[0] = (int)sqrt(a[0]);
        return;
    }
    Sqrt(a, b, n >> 1);
    for(int i = 0;i < n;++i)bi[i] = 0;
    for(int i = n;i < (n << 1);++i)Tmp[i] = 0;
    Inv(b, bi, n);
    for(int i = 0;i < n;++i)Tmp[i] = a[i];
    for(int i = n;i < (n << 1);++i)Tmp[i] = 0;
    NTT(Tmp, n << 1, 1);
    NTT(b, n << 1, 1);
    NTT(bi, n << 1, 1);
    for(int i = 0;i < (n << 1);++i)b[i] = 1LL * inv2 * (b[i] + 1LL * bi[i] * Tmp[i] % mod) % mod;
    NTT(b, n << 1, -1);
    for(int i = n;i < (n << 1);++i)b[i] = 0;
}
int main(){
    int N, n, m;
    scanf("%d%d", &m, &n);n++;
    for(int i = 1, x;i <= m;++i){
        scanf("%d", &x);
        if(x < n)f[x] = mod - 4; 
    }
    f[0] = 1;
 
    for(N = 1;N < n;N <<= 1);  
    Sqrt(f, g, N);
    g[0]++;
    memset(f, 0, sizeof(f));
    Inv(g, f, N);
    for(int i = 1;i < n;++i)printf("%d\n", ((f[i] << 1) % mod + mod) % mod);
    return 0;
}