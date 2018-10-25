bool Bfs(){
    memset(dep,-1,sizeof(dep));
    queue<int>Q; Q.push(S);dep[S] = 0;
    while(!Q.empty()){
        int u = Q.front();Q.pop();
        for(int i = he[u];i;i = e[i].nx){
            if(e[i].cap && dep[e[i].v] == -1){
                dep[e[i].v] = dep[u] + 1;
                Q.push(e[i].v);
            }
        }
    }
    return dep[T] != -1;
}
int Dfs(int x,int w){
    if(x == T || w == 0)return w;
    int res = 0;
    for(int &i = cur[x];i;i = e[i].nx){
        if(e[i].cap && dep[e[i].v] == dep[x]+1){
            int tmp = Dfs(e[i].v, min(e[i].cap, w));
            res += tmp; w -= tmp;
            e[i].cap -= tmp;e[i ^ 1].cap += tmp;
            if(w == 0)break;
        }
    }
    if(!res)dep[x] = -1;
    return res;
}
void Dinic(){
    int Flow = 0;
    while(Bfs()){
        memcpy(cur, he, sizeof(he));
        Flow += Dfs(S, inf);
    }
}
