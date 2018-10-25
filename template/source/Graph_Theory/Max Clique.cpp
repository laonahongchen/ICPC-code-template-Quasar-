//朴素写法
int n, Max[maxn], adj[maxn][maxn], e[maxn][maxn], ans;
bool Dfs(int cur, int tot){
  if(!cur){
    if(tot > ans){
      ans = tot;
      return 1;
    }
    else return 0;
  }
  for(int i = 1;i <= cur;++i){
    if(cur - i + 1 + tot <= ans)return 0;
    int u = adj[tot][i], nxt = 0;
    if(Max[u] + tot <= ans)return 0;
    for(int j = i + 1;j <= cur;++j){
      if(e[u][adj[tot][j]])adj[tot + 1][++nxt] = adj[tot][j];
    }
    if(Dfs(nxt, tot + 1))return 1;
  }
  return 0;
}
int MaxClique(){
  ans = 0;
  memset(Max, 0, sizeof(Max));
  for(int i = n;i > 0;--i){
    int cur = 0;
    for(int j = i + 1;j <= n;++j){
      if(e[i][j])adj[1][++cur] = j;
    }
    Dfs(cur, 1);
    Max[i] = ans;
  }
  return ans;
}
//高效写法
typedef bool BB[N]; struct Maxclique {
	const BB *e; int pk, level; const float Tlimit;
	struct Vertex { int i, d; Vertex (int i) : i (i), d (0) {}};
	typedef std::vector <Vertex> Vertices; Vertices V;
	typedef std::vector <int> ColorClass; ColorClass QMAX, Q;
	std::vector <ColorClass> C;
	static bool desc_degree (const Vertex &vi, const Vertex &vj) { return vi.d > vj.d; }
	void init_colors (Vertices &v) {
		const int max_degree = v[0].d;
		for (int i = 0; i < (int) v.size (); ++i)
			v[i].d = std::min (i, max_degree) + 1;
	}
	void set_degrees (Vertices &v) {
		for (int i = 0, j; i < (int) v.size (); ++i)
			for (v[i].d = j = 0; j < (int) v.size (); ++j)
				v[i].d += e[v[i].i][v[j].i];
	}
	struct StepCount { int i1, i2; StepCount () : i1 (0), i2 (0) {} };
	std::vector <StepCount> S;
	bool cut1 (const int pi, const ColorClass &A) {
		for (int i = 0; i < (int) A.size (); ++i)
			if (e[pi][A[i]]) return true; return false;
	}
	void cut2 (const Vertices &A, Vertices &B) {
		for (int i = 0; i < (int) A.size () - 1; ++i)
			if (e[A.back ().i][A[i].i]) B.push_back (A[i].i);
	}
	void color_sort (Vertices &R) { int j = 0, maxno = 1;
		int min_k = std::max ((int) QMAX.size () - (int) Q.size () + 1, 1);
		C[1].clear (); C[2].clear ();
		for (int i = 0; i < (int) R.size (); ++i) {
			int pi = R[i].i, k = 1; while (cut1 (pi, C[k])) ++k;
			if (k > maxno) maxno = k, C[maxno + 1].clear ();
			C[k].push_back (pi); if (k < min_k) R[j++].i = pi;
		}
		if (j > 0) R[j - 1].d = 0;
		for (int k = min_k; k <= maxno; ++k)
			for (int i = 0; i < (int) C[k].size (); ++i)
				R[j].i = C[k][i], R[j++].d = k;
	}
	void expand_dyn (Vertices &R) {
		S[level].i1 = S[level].i1 + S[level - 1].i1 - S[level].i2;
		S[level].i2 = S[level - 1].i1;
		while ((int) R.size ()) {
			if ((int) Q.size () + R.back ().d > (int) QMAX.size ()) {
				Q.push_back (R.back ().i); Vertices Rp; cut2 (R, Rp);
				if ((int) Rp.size ()) {
					if ((float) S[level].i1 / ++pk < Tlimit) degree_sort (Rp);
					color_sort (Rp); S[level].i1++, level++;
					expand_dyn (Rp); level--;
				} else if ((int) Q.size () > (int) QMAX.size ()) QMAX = Q;
				Q.pop_back ();
			} else return;
			R.pop_back ();
		}
	}
	void mcqdyn (int *maxclique, int &sz) {
		set_degrees (V); std::sort (V.begin (), V.end (), desc_degree);
		init_colors (V);
		for (int i = 0; i < (int) V.size () + 1; ++i) S[i].i1 = S[i].i2 = 0;
		expand_dyn (V); sz = (int) QMAX.size ();
		for (int i = 0; i < (int) QMAX.size (); ++i) maxclique[i] = QMAX[i];
	}
	void degree_sort (Vertices &R) {
		set_degrees (R); std::sort (R.begin (), R.end (), desc_degree);
	}
	Maxclique (const BB * conn, const int sz, const float tt = .025) : pk (0), level (1), Tlimit (tt) {
		for (int i = 0; i < sz; ++i) V.push_back (Vertex (i));
		e = conn, C.resize (sz + 1), S.resize (sz + 1);
	}
};
BB e[N]; int ans, sol[N];
int edge[N][N];
int col[N];
int main () {
	int n, m;
	while (std::cin >> n >> m && n) {
		if (n == 1) { std::cout << 1 << "\n"; continue; }
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) edge[i][j] = (i == j);
		for (int i = 0; i < m; ++i) {
			int a, b; std::cin >> a >> b;
			edge[a][b] = edge[b][a] = 1;
		}
		for (int i = 1; i < n; ++i) for (int j = 1; j < n; ++j) {
			int a = edge[0][i], b = edge[0][j];
			e[i - 1][j - 1] = (edge[i][j] == (a == b));
		}
		Maxclique mc (e, n - 1);
		mc.mcqdyn (sol, ans);
		std::cout << ans + 1 << "\n";
	}
}
