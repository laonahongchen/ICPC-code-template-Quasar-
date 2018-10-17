const int maxn = 100010;
int nodecnt,n,m;
int A[maxn];
struct Node{
	int len,root,nx[10];
}T[maxn*40];
 
void Init(){
	nodecnt = 0;
	T[0].len = 0;T[0].root = -1;
}
int Extend(int p,int c){
	int np = ++nodecnt;
	T[np].len = T[p].len + 1;
	for(;p != -1 && !T[p].nx[c];p = T[p].root)T[p].nx[c] = np;
	if(p == -1)T[np].root = 0;
	else {
		int q = T[p].nx[c];
		if(T[q].len == T[p].len + 1)T[np].root = q;
		else {
			int nw = ++nodecnt;
			T[nw] = T[q];
			T[nw].len = T[p].len + 1;
			for(;p != -1 && T[p].nx[c] == q;p = T[p].root)T[p].nx[c] = nw;
			T[q].root = T[np].root = nw;
		}
	}return np;
}
 
int ed,he[maxn],ind[maxn];
struct Edge{
	int v,nx;
	Edge(int _v,int _nx){v = _v;nx = _nx;}
	Edge(){;}
}e[maxn<<1];
void Add(int u,int v){
	e[++ed] = Edge(v,he[u]);he[u] = ed;
}
void Dfs(int x,int fa,int last){
	last = Extend(last,A[x]);
	for(int i = he[x];i;i = e[i].nx){
		int v = e[i].v;
		if(v == fa)continue;
		Dfs(v,x,last);
	}
}
int main(){
	freopen("zjoi15_substring.in","r",stdin);
	freopen("zjoi15_substring.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i)scanf("%d",&A[i]);
	for(int i = 1,u,v;i < n;++i){
		scanf("%d%d",&u,&v);
		Add(u,v);Add(v,u);
		ind[u]++;ind[v]++;
	}
	Init();
	for(int i = 1;i <= n;++i){
		if(ind[i] == 1)Dfs(i,0,0);
	}
	ll ans = 0;
	for(int i = 1;i <= nodecnt;++i){
		ans += 1LL*(T[i].len - T[T[i].root].len);
	}
	printf("%lld",ans);
//	while(1);
	return 0;
}
