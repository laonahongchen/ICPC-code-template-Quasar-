struct Query{
	int l, r, extra, i;
	friend bool operator < (const Query &a, const Query &b) {
		if(bid[a.l] != bid[b.l]) return bid[a.l] < bid[b.l];
		return a.r < b.r;
	}
} q[M];
int dfs_clock, st[N], ed[N], col[N << 1], id[N << 1];
void dfs(int x, int p){
	col[st[x] = ++dfs_clock] = w[x];
	id[st[x]] = x;
	for(auto y: g[x])
		if(y != p) dfs(y, x);
	col[ed[x] = ++dfs_clock] = w[x];
	id[ed[x]] = x;
}
void prepare(){
	dfs_clock = 0;
	dfs(1, 0);
	int BS = (int)sqrt(dfs_clock + 0.5);
	for(int i = 1; i <= dfs_clock; i++)
		bid[i] = (i + BS - 1) / BS;
	for(int i = 1; i <= m; i++){
		int a = q[i].l, b = q[i].r, c = lca(a, b);
		if(st[a] > st[b]) swap(a, b);
		if(c == a){
			q[i].l = st[a];
			q[i].r = st[b];
			q[i].extra = 0;
		}
		else{
			q[i].l = ed[a];
			q[i].r = st[b];
			q[i].extra = c;
		}
	}
	sort(q + 1, q + m + 1);
}
int curans, ans[M], cnt[N];
bool state[N];
void rev(int x){
	int &c = cnt[col[x]];
	curans -= !!c;
	c += (state[id[x]] ^= 1) ? 1 : -1;
	curans += !!c;
}
void solve(){
	prepare();
	curans = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(state, 0, sizeof(state));
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++){
		while(l < q[i].l) rev(l++);
		while(l > q[i].l) rev(--l);
		while(r < q[i].r) rev(++r);
		while(r > q[i].r) rev(r--);
		if(q[i].extra) rev(st[q[i].extra]);
		ans[q[i].i] = curans;
		if(q[i].extra) rev(st[q[i].extra]);
	}
}