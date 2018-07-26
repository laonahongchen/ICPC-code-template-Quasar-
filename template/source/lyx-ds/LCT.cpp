struct LCT
{
	int fa[N], c[N][2], rev[N], sz[N];

	void update(int o) {
		sz[o] = sz[c[o][0]] + sz[c[o][1]] + 1;
	}
	void pushdown(int o) {
		if(rev[o]) {
			rev[o] = 0;
			rev[c[o][0]] ^= 1;
			rev[c[o][1]] ^= 1;
			swap(c[o][0], c[o][1]);
		}
	}
	bool ch(int o) {
		return o == c[fa[o]][1];
	}
	bool isroot(int o) {
		return c[fa[o]][0] != o && c[fa[o]][1] != o;
	}
	void setc(int x, int y, bool d) {
		if(x) fa[x] = y;
		if(y) c[y][d] = x;
	}
	void rotate(int x) {
		if(isroot(x)) return;
		int p = fa[x], d = ch(x);
		if(isroot(p)) fa[x] = fa[p];
		else setc(x, fa(p), ch(p));
		setc(c[x][d^1], p, d);
		setc(p, x, d^1);
		update(p);
		update(x);
	}
	void splay(int x) {
		static int q[N], top;
		int y = q[top = 1] = x;
		while(!isroot(y)) q[++top] = y = fa[y];
		while(top) pushdown(q[top--]);
		while(!isroot(x)) {
			if(!isroot(fa[x]))
				rotate(ch(fa[x]) == ch(x) ? fa[x] : x);
			rotate(x);
		}
	}
	void access(int x) {
		for(int y = 0; x; y = x, x = fa[x])
			splay(x), c[x][1] = y, update(x);
	}
	void makeroot(int x) {
		access(x), splay(x), rev(x) ^= 1;
	}
	void link(int x, int y) {
		makeroot(x), fa[x] = y, splay(x);
	}
	void cut(int x, int y) {
		makeroot(x);
		access(y);
		splay(y);
		c[y][0] = fa[x] = 0;
	}
};
