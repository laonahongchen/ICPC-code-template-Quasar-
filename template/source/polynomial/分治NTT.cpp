//bzoj 3456 城市规划
const int mod = 1004535809;
const int phi = 1004535808;
const int maxn = (1 << 19) + 5;
const int G = 3;
 
int rev[maxn];
void NTT(int *a, int n, int type){
    int i, j, k, w, wn, pa, pb;
    for(int i = 1;i < n;++i){
        if(i > rev[i])swap(a[i], a[rev[i]]);
    }
    for(k = 2;k <= n;k <<= 1){
        wn = Pow(G, (type * phi / k % phi + phi) % phi);
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
        int inv = Pow(n, phi - 1);
        for(int i = 0;i < n;++i)a[i] = 1LL * a[i] * inv % mod;
    }
}
 
int fac[maxn], inv[maxn], c2[maxn], f[maxn], g[maxn], A[maxn], B[maxn], C[maxn];
void solve(int l, int r){
	if(l == r){
		f[l] = (c2[l] - 1LL * fac[l - 1] * f[l] % mod + mod) % mod;
		return; 
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	int L = mid - l + 1, R = r - l + 1;
	int n = 1, K = 0;
    for(n = 1, K = 0;n < L + R - 1;n <<= 1)++K;--K;
   	for(int i = 0;i < n;++i)A[i] = B[i] = C[i] = 0;
    for(int i = 1;i < n;++i){
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << K);
    }
	for(int i = l;i <= mid;++i)A[i - l] = 1LL * f[i] * inv[i - 1] % mod;
	for(int i = 1;i < R;++i)B[i] = g[i];
	NTT(A, n, 1);
	NTT(B, n, 1);
	for(int i = 0;i < n;++i)C[i] = 1LL * A[i] * B[i] % mod;
	NTT(C, n, -1);
	for(int i = mid + 1;i <= r;++i){
		f[i] = (f[i] + C[i - l]) % mod;
	}
	solve(mid + 1, r);
}
 
int main(){
	int n;scanf("%d", &n);
	fac[0] = 1;
	for(int i = 1;i <= n;++i){
		fac[i] = 1LL * fac[i - 1] * i % mod;
		int tmp = 1LL * i * (i - 1) / 2 % (mod - 1);
		c2[i] = Pow(2, tmp);
	}
	inv[n] = Pow(fac[n], mod - 2);
	for(int i = n - 1;i >= 0;--i){
		inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;
	}
	for(int i = 1;i <= n;++i){
		g[i] = 1LL* c2[i] * inv[i] % mod;
	}
	solve(1, n);
	printf("%d\n", f[n]);
	return 0;
}