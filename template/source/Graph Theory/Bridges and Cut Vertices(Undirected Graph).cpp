void Targan(int x, int fa){
	dfn[x] = low[x] = ++cnt;
	int son = 0;
	for(int i = he[x], v;i;i = e[i].nx){
		v = e[i].v;
		if(v == fa)continue;	
		if(!dfn[v]){
			Targan(v, x);
			++son; 
			low[x] = min(low[x], low[v]);
			if(low[v] > dfn[x])bridge[x] = 1;
			if(low[v] >= dfn[x])cut[x] = 1;
		}
		else low[x] = min(low[x], dfn[v]);
	}
	if(!fa && son == 1)cut[x] = 0;
}
