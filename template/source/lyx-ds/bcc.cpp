#define SZ(x) ((int)x.size())

const int N = 400005; // N开2倍点数，因为新树会加入最多n个新点
const int M = 200005;

vector<int> g[N];

int bccno[N], bcc_cnt;
vector<int> bcc[N];
bool iscut[N];

struct Edge {
	int u, v;
} stk[M << 2];
int top; // 注意栈大小为边数4倍
int dfn[N], low[N], dfs_clock;

void dfs(int x, int fa)
{
	low[x] = dfn[x] = ++dfs_clock;
	int child = 0;
	for(int i = 0; i < SZ(g[x]); i++) {
		int y = g[x][i];
		if(!dfn[y]) {
			child++;
			stk[++top] = (Edge){x, y};
			dfs(y, x);
			low[x] = min(low[x], low[y]);
			if(low[y] >= dfn[x]) {
				iscut[x] = true;
				bcc[++bcc_cnt].clear();
				for(;;) {
					Edge e = stk[top--];
					if(bccno[e.u] != bcc_cnt) { bcc[bcc_cnt].push_back(e.u); bccno[e.u] = bcc_cnt; }
					if(bccno[e.v] != bcc_cnt) { bcc[bcc_cnt].push_back(e.v); bccno[e.v] = bcc_cnt; }
					if(e.u == x && e.v == y) break;
				}
			}
		} else if(y != fa && dfn[y] < dfn[x]) {
			stk[++top] = (Edge){x, y};
			low[x] = min(low[x], dfn[y]);
		}
	}
	if(fa == 0 && child == 1) iscut[x] = false;
}

void find_bcc() // 求点双联通分量，需要时手动1到n清空，1-based
{
	memset(dfn, 0, sizeof(dfn));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	dfs_clock = bcc_cnt = 0;
	for(int i = 1; i <= n; i++)
		if(!dfn[i])
			dfs(i, 0);
}

vector<int> G[N];

void prepare() { // 建出缩点后的树
	for(int i = 1; i <= n + bcc_cnt; i++)
		G[i].clear();
	for(int i = 1; i <= bcc_cnt; i++) {
		int x = i + n;
		for(int j = 0; j < SZ(bcc[i]); j++) {
			int y = bcc[i][j];
			G[x].push_back(y);
			G[y].push_back(x);
		}
	}
}
