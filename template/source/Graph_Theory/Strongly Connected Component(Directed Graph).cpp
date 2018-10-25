void Targan(int x){
  dfn[x] = low[x] = ++cnt;
  sta[++stm] = x;ins[x] = 1;
  for(int i = he[x], v;i;i = e[i].nx){
      v = e[i].v;
      if(!dfn[v]){
          Targan(v);
          low[x] = min(low[x], low[v]);
    	}
       else if(ins[v]){
          low[x] = min(low[x], dfn[v]);
       }
  }
  if(dfn[x] == low[x]){
	  ++scc;
	  while(sta[stm] != x){
	     ins[sta[stm]] = 0;
	     T[scc].poi.push_back(sta[stm--]);
	  }
	  ins[sta[stm]] = 0;
	  T[scc].poi.push_back(sta[stm--]);
  }
}
