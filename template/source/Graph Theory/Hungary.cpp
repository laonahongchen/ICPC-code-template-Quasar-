int Dfs(int x){
	for(int i = he[x], v;i;i = e[i].nx){
		v = e[i].v;
		if(vis[v])continue;
		vis[v] = 1;
		if(!cy[v] || Dfs(cy[v])){
			cx[x] = v, cy[v] = x;
			return 1;
		}
	}
	return 0;
}
int Hungary(){
	int ans = 0;
	for(int i = 1;i <= n;i++){
		if(!cx[i]){
			memset(vis, 0, sizeof(vis));
			ans += Dfs(i);
		}
	}
	return ans;
}
