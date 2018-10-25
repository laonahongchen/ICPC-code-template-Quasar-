//边的编号从2开始
void Targan(int x, int last){
	int ch = 0;
	dfn[x] = low[x] = ++dfsclock;
	for(int i = he[x], v; i; i = e[i].nx){
		if(i == last)continue;
		v = e[i].v;
		if(!dfn[v]){
			sta[++stm] = e[i], ch++;
			Targan(v, i ^ 1);
			low[x] = min(low[x], low[v]);
			if(low[v] >= dfn[x]){
				iscut[x] = 1;
				bcc[++bccnt].clear();
				while(1){
					Edge t = sta[stm--];
					if(bccno[t.u] != bccnt)bcc[bccnt].push_back(t.u), bccno[t.u] = bccnt;
					if(bccno[t.v] != bccnt)bcc[bccnt].push_back(t.v), bccno[t.v] = bccnt;
					if(t.u == u && t.v == v)break;
				}
			}
		}
		else if(dfn[v] < dfn[x]){
			sta[++stm] = e[i];
			low[x] = min(low[x], dfn[v]);
		}
	}
	if(last == 0 && ch == 1)iscut[u] = 0;
}