/*
Suffix Array
求出现k次的最长重复子串：
二分答案,将后缀分成若干组,根据height判断是否有一个组的后缀个数不小于k。

本质不同的子串的个数:sum{n-sa[i]-height[i]}
*/
int Len;
int sa[maxn], Rank[maxn], h[maxn], r[maxn], wa[maxn << 1], wb[maxn << 1], Ws[maxn];
bool cmp(int *y, int a, int b, int len){
	return y[a] == y[b] && y[a + len] == y[b + len];
}
void Da(int n, int m){
	int i, j, p, *x = wa, *y =wb;
	for(i = 0;i < m;++i)Ws[i] = 0;
	for(i = 0;i < n;++i)Ws[x[i] = r[i]]++;
	for(i = 1;i < m;++i)Ws[i] += Ws[i - 1];
	for(i = n - 1;i >= 0;--i)sa[--Ws[x[i]]] = i; 
	for(j = 1, p = 0;p < n;j <<= 1, m = p){
		for(p = 0, i = n - j;i < n;++i)y[p++] = i;
		for(i = 0;i < n;++i){
			if(sa[i] >= j)y[p++] = sa[i] - j;
		}
		for(i = 0;i < m;++i)Ws[i] = 0;
		for(i = 0;i < n;++i)Ws[x[y[i]]]++;
		for(i = 1;i < m;++i)Ws[i] += Ws[i - 1];
		for(i = n - 1;i >= 0;--i)sa[--Ws[x[y[i]]]] = y[i];
		for(swap(x, y), i = 1, p = 1, x[sa[0]] = 0;i < n;++i){
			x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p ++;
		}
	}
}
void Calheight(int n){
	int i, j, k = 0;
	for(i = 1;i <= n;++i)Rank[sa[i]] = i;
	for(i = 0;i < n;h[Rank[i++]] = k){
		for(k > 0 ? k-- : 0, j = sa[Rank[i] - 1];r[i + k] == r[j + k];++k);
	}
}
int Log[maxn], f[maxn << 1][20];
void ST(int n){
	Log[1] = 0;
	for(int i = 2;i <= n;++i){
		Log[i] = Log[i - 1];
		if((1 << (Log[i] + 1)) == i)Log[i]++;
	}
	memset(f, 0x3f, sizeof(f));
	for(int i = 1;i <= n;++i)f[i][0] = h[i];
	for(int j = 1;(1 << j) <= n;++j){
		for(int i = 1;i <= n;++i){
			f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
}
int LCP(int x, int y){
	if(x == y)return Len - x;
	x = Rank[x], y = Rank[y];
	if(x > y)swap(x, y);++x;
	int len = y - x + 1;
	return min(f[x][Log[len]], f[y - (1 <<Log[len]) + 1][Log[len]]);
}

