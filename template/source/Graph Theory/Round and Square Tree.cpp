//圆点:原图中的点，方点:每个点双连通分量新添加的的点。
//nodecnt从n+1开始作为方点的编号
void Targan(int x, int last){
	dfn[x] = low[x] = ++dfsclock;
	sta[++stm] = x;
	for(int i = he[x], v; i; i = e[i].nx){
		if(i == last)continue;
		v = G.e[i].v;
		if(!dfn[v]){
			Targan(v, i ^ 1);
			low[x] = min(low[x], low[v]);
			if(low[v] >= dfn[x]){
				addedge(++nodecnt, x);
				while(stm && sta[stm] != v){
					addedge(nodecnt, sta[stm--]);
				}
				addedge(nodecnt, sta[stm--]);			
			}
		}
		else low[x] = min(low[x], dfn[v]);
	}
}
