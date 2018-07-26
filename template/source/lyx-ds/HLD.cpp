int n;

vector<int> g[N];

int son[N], top[N];
int dep[N], sz[N], fa[N];
int dfn[N], pos[N], segn;

void dfs(int x, int p) {
	sz[x] = 1;
	fa[x] = p;
	son[x] = -1;
	dep[x] = dep[p] + 1;
	for(auto y: g[x]) {
		if(y == p) continue;
		dfs(y, x);
		sz[x] += sz[y];
		if(son[x] == -1 || sz[son[x]] < sz[y])
			son[x] = y;
	}
}
void DFS(int x, int tp) {
	top[x] = tp;
	dfn[pos[x] = ++segn] = x;
	if(~son[x]) DFS(son[x], tp);
	for(auto y: g[x])
		if(y != fa[x] && y != son[x])
			DFS(y, y);
}
void modify(int x, int y, int c)
{
	qv = c;
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]])
			swap(x, y);
		ql = pos[top[x]]; qr = pos[x];
		seg_modify(1, 1, segn);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	ql = pos[x]; qr = pos[y];
	seg_modify(1, 1, segn);
}
bool flag_res;
void seg_query(int o, int l, int r) {
	if(ql <= l && r <= qr) {
		if(flag_res)
			res = res + val[o];
		else {
			res = val[o];
			flag_res = true;
		}
		return;
	}
	pushdown(o, l, r);
	if(ql <= mid) seg_query(Lc);
	if(mid < qr) seg_query(Rc);
}
int query(int x, int y) // 点操作版
	// 边操作每个点对应其父边（根除外）
{
	bool flag_pre = false;
	bool flag_suf = false;
	while(top[x] != top[y])
	{
		flag_res = false;
		if(dep[top[x]] > dep[top[y]])
		{
			ql = pos[top[x]]; qr = pos[x];
			seg_query(1, 1, segn);
			if(flag_pre)
				pre = pre + reverse(res);
			else
			{
				pre = reverse(res);
				flag_pre = true;
			}
			x = fa[top[x]];
		}
		else
		{
			ql = pos[top[y]]; qr = pos[y];
			seg_query(1, 1, segn);
			if(flag_suf)
				suf = res + suf;
			else
			{
				suf = res;
				flag_suf = true;
			}
			y = fa[top[y]];
		}
	}
	flag_res = false;
	if(dep[x] < dep[y])
	{
		ql = pos[x]; qr = pos[y];
		seg_query(1, 1, segn);
	}
	else
	{
		ql = pos[y]; qr = pos[x];
		seg_query(1, 1, segn);
		res = reverse(res);
	}
	if(flag_pre) res = pre + res;
	if(flag_suf) res = res + suf;
	return res.mx;
}
