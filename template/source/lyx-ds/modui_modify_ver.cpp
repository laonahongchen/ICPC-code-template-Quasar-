// uva12345
// single testcase
#include <bits/stdc++.h>

using namespace std;

const int N = 50005;
const int MAXV = 1e6 + 5;

int n, m;
int a[N];
int bid[N];
int qn, modn;

struct Query
{
	int l, r, last, i;

	friend bool operator < (const Query &a, const Query &b)
	{
		if(bid[a.l] != bid[b.l])
			return bid[a.l] < bid[b.l];
		if(bid[a.r] != bid[b.r])
			return bid[a.r] < bid[b.r];
		return a.last < b.last;
	}
} q[N];

struct Modify
{
	int x, to, from;
} mod[N];

void input()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		static char op[2];
		scanf("%s%d%d", op, &x, &y);
		x++;
		if(op[0] == 'Q')
		{
			++qn;
			q[qn] = (Query){x, y, modn, qn};
		}
		else if(op[0] == 'M')
		{
			mod[++modn] = (Modify){x, y, a[x]};
			a[x] = y;
		}
		else assert(false);
	}
	int BS = (int)pow(n + 0.5, 2.0 / 3.0);
	for(int i = 1; i <= n; i++)
		bid[i] = (i + BS - 1) / BS;
}

int ans[N];
int curans;
int cnt[MAXV];
bool state[N];

void modify(int x)
{
	int &c = cnt[a[x]];
	curans -= !!c;
	c += (state[x] ^= 1) ? 1 : -1;
	curans += !!c;
}

void change(int i, bool type)
{
	int x = mod[i].x;
	int newv = type ? mod[i].to : mod[i].from;
	if(state[x])
	{
		modify(x);
		a[x] = newv;
		modify(x);
	}
	else
	{
		a[x] = newv;
	}
}

void solve()
{
	sort(q + 1, q + qn + 1);
	int l = 1, r = 0, now = modn;
	for(int i = 1; i <= qn; i++)
	{
		while(q[i].last < now) change(now--, 0);
		while(q[i].last > now) change(++now, 1);
		while(q[i].l < l) modify(--l);
		while(q[i].l > l) modify(l++);
		while(q[i].r < r) modify(r--);
		while(q[i].r > r) modify(++r);
		ans[q[i].i] = curans;
	}
	for(int i = 1; i <= qn; i++)
		printf("%d\n", ans[i]);
}

int main()
{
	input();
	solve();
	return 0;
}
