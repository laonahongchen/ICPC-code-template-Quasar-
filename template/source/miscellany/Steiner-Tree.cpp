void spfa(int state) {
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (auto v: g[now]) {
			double len = d[now][v];
			if (f[v][st[v] | state] > f[now][state] + len) {
				f[v][st[v] | state] = f[now][state] + len;
				if ((st[v] | state) != state || vis[v][state])
					continue;
				vis[v][state] = true;
				q.push(v);
			}
		}
		vis[now][state] = false;
	}
}

double solve() {
	int endst = 1 << k;

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < endst; j++)
			f[i][j] = 1e18;

	for (int i = 1; i <= n; i++) f[i][st[i]] = 0;
	for (int j = 1; j < endst; j++) {
		for (int i = 1; i <= n; i++) {
			if (!st[i] || (st[i] & j)) {
				for (int sub = (j-1)&j; sub; sub = (sub-1) & j) {
					int x = sub | st[i], y = (j - sub) | st[i];
					update(f[i][j], f[i][x] + f[i][y]);
				}
			}
			if (f[i][j] < 1e18) {
				q.push(i);
				vis[i][j] = true;
			}
		}
		spfa(j);
	}

	double ans = 1e18;
	for (int i = 1; i <= n; i++) {
		update(ans, f[i][endst - 1]);
	}
	return ans;
}
