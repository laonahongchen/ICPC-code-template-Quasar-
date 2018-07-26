#include <bits/stdc++.h>

using namespace std;

const int N = 40005;
const int M = 100005;
const int LOGN = 17;

int n, m;
int w[N];
vector<int> g[N];
int bid[N << 1];

struct Query
{
	int l, r, extra, i;
	friend bool operator < (const Query &a, const Query &b) 
	{
		if(bid[a.l] != bid[b.l])
			return bid[a.l] < bid[b.l];
		return a.r < b.r;
	}
} q[M];

void input()
{
	vector<int> vs;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &w[i]);
		vs.push_back(w[i]);
	}
	sort(vs.begin(), vs.end());
	vs.resize(unique(vs.begin(), vs.end()) - vs.begin());
	for(int i = 1; i <= n; i++)
		w[i] = lower_bound(vs.begin(), vs.end(), w[i]) - vs.begin() + 1;
	for(int i = 2; i <= n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].i = i;
	}
}

int dfs_clock;
int st[N], ed[N];
int fa[N][LOGN], dep[N];
int col[N << 1];
int id[N << 1];

void dfs(int x, int p)
{
	col[st[x] = ++dfs_clock] = w[x];
	id[st[x]] = x;
	fa[x][0] = p; dep[x] = dep[p] + 1;
	for(int i = 0; fa[x][i]; i++)
		fa[x][i + 1] = fa[fa[x][i]][i];
	for(auto y: g[x])
		if(y != p)
			dfs(y, x);
	col[ed[x] = ++dfs_clock] = w[x];
	id[ed[x]] = x;
}

int lca(int x, int y)
{
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = LOGN - 1; i >= 0; i--)
		if(dep[fa[x][i]] >= dep[y])
			x = fa[x][i];
	if(x == y) return x;
	for(int i = LOGN - 1; i >= 0; i--)
		if(fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void prepare()
{
	dfs_clock = 0;
	dfs(1, 0);
	int BS = (int)sqrt(dfs_clock + 0.5);
	for(int i = 1; i <= dfs_clock; i++)
		bid[i] = (i + BS - 1) / BS;
	for(int i = 1; i <= m; i++)
	{
		int a = q[i].l;
		int b = q[i].r;
		int c = lca(a, b);
		if(st[a] > st[b]) swap(a, b);
		if(c == a)
		{
			q[i].l = st[a];
			q[i].r = st[b];
			q[i].extra = 0;
		}
		else
		{
			q[i].l = ed[a];
			q[i].r = st[b];
			q[i].extra = c;
		}
	}
	sort(q + 1, q + m + 1);
}

int curans;
int ans[M];
int cnt[N];
bool state[N];

void rev(int x)
{
	int &c = cnt[col[x]];
	curans -= !!c;
	c += (state[id[x]] ^= 1) ? 1 : -1;
	curans += !!c;
}

void solve()
{
	prepare();
	curans = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(state, 0, sizeof(state));

	int l = 1, r = 0;
	for(int i = 1; i <= m; i++)
	{
		while(l < q[i].l) rev(l++);
		while(l > q[i].l) rev(--l);
		while(r < q[i].r) rev(++r);
		while(r > q[i].r) rev(r--);
		if(q[i].extra) rev(st[q[i].extra]);
		ans[q[i].i] = curans;
		if(q[i].extra) rev(st[q[i].extra]);
	}
	for(int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
}

int main()
{
	input();
	solve();
	return 0;
}
