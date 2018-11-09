void build() {
	//按照dfs序排序，清空时不能只根据边。
	sort(lst + 1, lst + cnt + 1, cmp);
	cnt = unique(lst + 1, lst + cnt + 1) - lst - 1;
	sta[stm = 1] = lst[1];
	for(int i = 2, x; i <= cnt; ++i) {
		x = lst[i];
		int lc = lca(x, sta[stm]);
		for(; stm > 1 && dep[sta[stm - 1]] > dep[lc]; stm--){
			addedge(sta[stm - 1], sta[stm]);
		}
		if(stm && dep[sta[stm]] > dep[lc]) {
			addedge(lc, sta[stm--]);
		}
		if(!stm || sta[stm] != lc) sta[++stm] = lc;
		sta[++stm] = x;
	}
	for(; stm > 1; --stm) addedge(sta[stm - 1], sta[stm]);
}
