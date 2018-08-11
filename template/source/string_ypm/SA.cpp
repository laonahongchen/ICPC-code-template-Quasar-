#define ws wws
const int MAXN = 201010;
int wa[MAXN], wb[MAXN], wv[MAXN], ws[MAXN];
int sa[MAXN], rk[MAXN], height[MAXN];
char s[MAXN];

inline bool cmp(int *r, int a, int b, int l)
{
	return r[a] == r[b] && r[a + l] == r[b + l];
}

void SA(char *r, int *sa, int n, int m)
{
	int *x = wa, *y = wb;
	for(int i = 1; i <= m; i++)ws[i] = 0;
	for(int i = 1; i <= n; i++)ws[x[i] = r[i]]++;
	for(int i = 1; i <= m; i++)ws[i] += ws[i - 1];
	for(int i = n; i > 0; i--)sa[ ws[x[i]]-- ] = i;
	for(int j = 1, p = 0; p < n; j <<= 1, m = p)
	{
		p = 0;
		for(int i = n - j + 1; i <= n; i++)y[++p] = i;
		for(int i = 1; i <= n; i++)if(sa[i] > j) y[++p] = sa[i] - j;
		for(int i = 1; i <= n; i++)wv[i] = x[y[i]];
		for(int i = 1; i <= m; i++)ws[i] = 0;
		for(int i = 1; i <= n; i++)ws[wv[i]]++;
		for(int i = 1; i <= m; i++)ws[i] += ws[i - 1];
		for(int i = n; i > 0; i--)sa[ ws[wv[i]]-- ] = y[i];
		swap(x, y);
		x[sa[1]] = p = 1;
		for(int i = 2; i <= n; i++)
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p : ++p;
	}
}

void getheight(char *r, int *sa, int *rk, int *h, int n)
{
	for(int i = 1; i <= n; i++)
		rk[sa[i]] = i;
	for(int i = 1, p = 0; i <= n; i++, p ? p-- : 0)
	{
		int j = sa[rk[i] - 1];
		while(r[i + p] == r[j + p])
			p++;
		h[rk[i]] = p;
	}	
}

