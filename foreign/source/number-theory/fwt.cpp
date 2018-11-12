void FWT(LL *a, int n) {
	for(int h = 2; h <= n; h <<= 1)
		for(int j = 0; j < n; j += h)
			for(int k = j; k < j + h / 2; k++) {
				LL u = a[k], v = a[k + h / 2];
				// xor: a[k] = (u + v) % MOD; a[k + h / 2] = (u - v + mo) % MOD;
				// and: a[k] = (u + v) % MOD; a[k + h / 2] = v;
				// or: a[k] = u; a[k + h / 2] = (u + v) % MOD;
			}
}
void IFWT(LL *a, int n) {
	for(int h = 2; h <= n; h <<= 1)
		for(int j = 0; j < n; j += h)
			for(int k = j; k < j + h / 2; k++) {
				LL u = a[k], v = a[k + h / 2];
				// xor: a[k] = mul((u + v) % MOD, inv2); 
				//		a[k + h / 2] = mul((u - v + MOD) % MOD, inv2);
				// and: a[k] = (u - v + MOD) % MOD; a[k + h / 2] = v;
				// or: a[k] = u; a[k + h / 2] = (v - u + MOD) % MOD;
			}
}
void multiply(LL *a, LL *b, LL *c, int len) {
	int l = 1; while(l < len) l <<= 1;
	len = l; FWT(a, len); FWT(b, len);
	for(int i = 0; i < len; i++) c[i] = mul(a[i], b[i]);
	IFWT(c, len);
}

