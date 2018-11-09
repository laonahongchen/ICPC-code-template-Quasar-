//{(mod,G)}={(81788929,7),(101711873,3),(167772161,3),(377487361,7),(998244353,3)
//,(1224736769,3),(1300234241,3),(1484783617,5)}
void NTT(int *a, int n, int type){
	int i, j, k, w, wn, pa, pb;
	for(i = 1; i < n; ++i) {
		if(i > rev[i]) swap(a[i], a[rev[i]]);
	}
	for(k = 2; k <= n; k <<= 1){
		wn = Pow(G, (type * phi / k % phi + phi) % phi, mod);
		for(j = 0; j < n; j += k){
			w = 1;
			for(i = 0; i < (k >> 1); ++i, w = 1LL * w * wn % mod){
				pa = a[i + j];
				pb = 1LL * w * a[i + j + (k >> 1)] % mod;
				a[i + j] = (pa + pb) % mod;
				a[i + j + (k >> 1)] = (pa - pb + mod) % mod;
			}
		}
	}
	if(type == -1){
		int inv = Pow(n, phi - 1, mod);
		for(int i = 0;i < n;++i)a[i] = 1LL * a[i] * inv % mod;
	}
}
void mul(int *a, int n, int *b, int m, int *c){
	int K, N;
	for(N = 1, K = 0; N <= n + m - 1; N <<= 1, K++); K--;
	for(int i = 1; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << K);
	FFT(a, N, 1);FFT(b, N, 1);
	for(int i = 0; i < N; ++i) c[i] = 1LL * a[i] * b[i] % mod;
	FFT(c, N, -1);
}
