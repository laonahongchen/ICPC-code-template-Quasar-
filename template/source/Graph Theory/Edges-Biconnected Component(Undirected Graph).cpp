//边的编号从2开始
void Targan(int x, int last){
	dfn[x] = low[x] = ++cnt;
	for(int i = he[x], v;i;i = e[i].nx){
		v = e[i].v;
		if(i == last)continue;	
		if(!dfn[v]){
			Targan(v, i ^ 1);
			low[x] = min(low[x], low[v]);
			if(low[v] > dfn[x])bridge[x] = 1;
		}
		else low[x] = min(low[x], dfn[v]);
	}
}
void Dfs(int x, int last){
	vis[x] = 1;
	bccno[x] = bccnt;
	bcc[bccnt].push_back(x);
	for(int i = he[x], v; i; i = e[i].nx){
		if(i == last || bridge[i])continue;
		v = e[i].v;
		if(!vis[v])Dfs(v, i ^ 1);
	}
}
void Find_ecc(){
	bccnt = 0;
	for(int i = 1; i <= n; ++i){
		if(!dfn[i])Targan(i, 0);
	}
	for(int i = 1; i <= n; ++i){
		if(!vis[i]){
			bccnt++;
			bcc[bccnt].clear();
			Dfs(i, 0);
		}
	}
}