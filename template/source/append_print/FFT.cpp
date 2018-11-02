const int MAXN = (1 << 18) + 10;
const double pi = acos(-1);
int rev[MAXN];
struct Complex{
	double x, y;
	Complex(double _x = 0, double _y = 0){x = _x;y = _y;}
};
Complex operator + (const Complex &a, const Complex &b){
	return Complex(a.x + b.x, a.y + b.y);
}
Complex operator - (const Complex &a, const Complex &b){
	return Complex(a.x - b.x, a.y - b.y);
}
Complex operator * (const Complex &a, const Complex &b){
	return Complex(a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y);
}
Complex operator * (const Complex &a, const double &b){
	return Complex(a.x * b, a.y * b);
}
void FFT(Complex *a, int n, int type){
	int i, j, k;
	for(i = 1; i < n; ++i){
		if(i > rev[i]) swap(a[i], a[rev[i]]);
	}
	Complex w, wn, pa, pb;
	for(k = 2; k <= n; k <<= 1){
		wn = Complex(cos(2.0 * pi * type / k), sin(2.0 * pi * type / k));
		for(j = 0; j < n; j += k){
			for(i = 0, w = Complex(1); i < (k >> 1); ++i, w = w * wn){
				pa = a[i + j], pb = w * a[i + j + (k >> 1)];
				a[i + j] = pa + pb;
				a[i + j + (k >> 1)] = pa - pb;
			}
		}
	}
	if(type == -1){
		double inv = 1.0 / n;
		for(i = 0; i < n; ++i) a[i] = a[i] * inv;
	}
}
void mul(Complex *a, int n, Complex *b, int m, Complex *c){
	int K, N;
	for(N = 1, K = 0; N < n + m - 1; N <<= 1, K++);K--;
	for(int i = 1; i < N; ++i){
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << K);
	}
	FFT(a, N, 1);
	FFT(b, N, 1);
	for(int i = 0; i < N; ++i) c[i] = a[i] * b[i];
	FFT(c, N, -1);
}