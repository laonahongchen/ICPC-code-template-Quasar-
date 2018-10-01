void VirtualTree(){
	sort(Q + 1, Q + s + 1, cmp);
	sta[stm = 1] = Q[1];
	for(int i = 2, x; i <= s; ++i){
		x = Q[i];
		int lca = Lca(x, sta[stm]);
		for(; stm > 1 && dep[sta[stm - 1]] >= dep[lca]; stm--){
			addedge(sta[stm - 1], sta[stm]);
		}
		addedge(lca, sta[stm--]);
		if(sta[stm] != lca)sta[++stm] = lca;
		sta[++stm] = x;
	}
	for(; stm > 1; --stm)addedge(sta[stm - 1], sta[stm]);
}
