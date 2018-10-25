bool Spfa(){
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	queue<int>Q; Q.push(S);
	vis[S] = 1;dis[S] = 0;val[S] = inf;
	while(!Q.empty()){
		int u = Q.front();Q.pop();vis[u] = 0;
		for(int i=he[u];i;i=e[i].nx){
			int v = e[i].v;
			if(e[i].cap && dis[v]>dis[u]+e[i].w){
				dis[v] = dis[u]+e[i].w;
				val[v] = min(val[u],e[i].cap);
				pre[v] = i;
				if(!vis[v])vis[v] = 1,Q.push(v);
			}
		}
	}
	if(dis[T]==inf)return 0;
	int u = T;
	Flow += val[T];Cost += val[T]*dis[T];
	while(u!=S){
		e[pre[u]].cap -= val[T];
		e[pre[u]^1].cap += val[T];
		u = e[pre[u]^1].v;
	}return 1;
}
void Mincost(){
	Flow = Cost =0;
	while(Spfa());
	printf("%d",Cost);
}
