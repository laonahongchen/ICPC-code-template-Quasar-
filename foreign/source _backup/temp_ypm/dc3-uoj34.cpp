//dc3, 1-based
//r数组开0~n, n + 1个元素，其中0~n - 1存字符串的ascii码(>0)，r[n] = 0;
//执行完后sa[0]舍弃不用，sa[1~n]是从0开始的sa数组，将sa[i]++后为正常1-based的sa数组
#include <bits/stdc++.h>
#define rank RANK
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb))
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb) * 3 + 2)
using namespace std;
const int N = 101010;

int wa[N], wb[N], wv[N], wss[N];
int r[N * 3], sa[N * 3], rank[N], height[N];
char s[N];

bool c0(int *r, int a, int b)
{
	return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}

int c12(int k, int *r, int a, int b)
{
	if(k == 2)
		return r[a] < r[b] || (r[a] == r[b] && c12(1, r, a + 1, b + 1));
	else
		return r[a] < r[b] || (r[a] == r[b] && wv[a + 1] < wv[b + 1]);
}

void sort(int *r, int *a, int *b, int n, int m)
{
	memset(wss, 0, sizeof(*wss) * (m + 2));
	for(int i = 0; i < n; i++) wss[wv[i] = r[a[i]]]++;
	for(int i = 1; i < m; i++) wss[i] += wss[i - 1];
	for(int i = n - 1; i >= 0; i--) b[ --wss[wv[i]] ] = a[i];
}

void dc3(int *r, int *sa, int n, int m)
{
	int *rn = r + n, *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
	r[n] = r[n + 1] = 0;
	for(int i = 0; i < n; i++)
		if(i % 3 != 0)
			wa[tbc++] = i;
	sort(r + 2, wa, wb, tbc, m);
	sort(r + 1, wb, wa, tbc, m);
	sort(r, wa, wb, tbc, m);
	rn[F(wb[0])] = 0;
	p = 1;
	for(int i = 1; i < tbc; i++)
		rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
	if(p < tbc) 
		dc3(rn, san, tbc, p);
	else
		for(int i = 0; i < tbc; i++)
			san[rn[i]] = i;
	for(int i = 0; i < tbc; i++)
		if(san[i] < tb)
			wb[ta++] = san[i] * 3;
	
	if(n % 3 == 1)
		wb[ta++] = n - 1;
	sort(r, wb, wa, ta, m);
	for(int i = 0; i < tbc; i++)
		wv[wb[i] = G(san[i])] = i;
	

	
	p = 0;
	int i = 0, j = 0;
	for(;i < ta && j < tbc; p++)
		sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
	for(; i < ta; p++)
		sa[p] = wa[i++];
	for(; j < tbc; p++)
		sa[p] = wb[j++];
}

void getheight(char s[], int sa[], int n)
{
	for(int i = 1; i <= n; i++)
		rank[sa[i]] = i;
	for(int p = 0, i = 1; i <= n; i++, p = (p) ? p - 1 : p)
		if(rank[i] > 1)
		{
			int j = sa[rank[i] - 1];
			while(s[i + p] == s[j + p])
				p++;
			height[rank[i]] = p;
		}
}


int main()
{
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for(int i = 0; i <= n; i++)// <= n !!!
		r[i] = s[i + 1];
	dc3(r, sa, n + 1, 255);//now the value of sa is from 0 to n - 1;
	for(int i = n; i ; i--)//after this operation, the value of sa is from 1 to n
		sa[i]++;
	getheight(s, sa, n);
	for(int i = 1;i <= n; i++)
		printf("%d ", sa[i]);
	puts("");
	for(int i = 2; i <= n; i++)
		printf("%d ", height[i]);
	puts("");
}
