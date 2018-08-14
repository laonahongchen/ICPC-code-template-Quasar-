/*一个无向图是弦图当且仅当他是一个完美消除序列。
最小染色数 = 最大团：在完美序列从后向前选。
最大独立集 = 最小团覆盖：在完美序列从前向后选。*/ 
int label[maxn], seq[maxn], pos[maxn], flag[maxn], vis[maxn], lst[maxn], clo[maxn];
struct Node{
  int u, lab;
  Node(){;}
  Node(int _u, int _lab){u = _u, lab = _lab;}
};
bool operator < (const Node &a, const Node &b){
  return a.lab < b.lab;
}
void Mcs(){
  for(int i = 1;i <= n;++i)Q.push(Node(i, 0));
  for(int t = n;t > 0;--t){
    while(pos[Q.top().u])Q.pop();
    int u = Q.top().u;Q.pop();
    pos[u] = t;
    for(int i = 0, v;i < G[u].size();++i){
      v = G[u][i];
      if(!pos[v]){
    	label[v]++;
    	Q.push(Node(v, label[v]));
      }
    }
  }
  for(int i = 1;i <= K;++i)seq[pos[i]] = i;
}
bool Check(){
  for(int i = n, u, t, v;i > 0;--i){
    u = seq[i], t = 0;
    for(int j = 0;j < G[u].size();++j){
      if(v = G[u][j], pos[v] > pos[u])lst[++t] = v;
    }
    if(!t)continue;
    v = lst[1];
    for(int j = 2;j <= t;++j){
      if(pos[lst[j]] < pos[v])v = lst[j];
    }
    for(int j = 0;j < G[v].size();++j)vis[G[v][j]] = i;
    for(int j = 1;j <= t;++j){
       if(lst[j] != v && vis[lst[j]] != i)return 0;
    }
  }
  return 1;
}
int Setcolor(){
  int ans = 0;
  for(int i = n, j, u;i > 0;--i){
    u = seq[i];
    for(j = 0;j < G[u].size();++j)vis[clo[G[u][j]]] = i;
    for(j = 1;vis[j] == i;++j);
    clo[u] = j;
    ans = max(ans, j);
  }
  return ans;
}
int Independent_Set(){
  int ans = 0;
  for(int i = 1, u, fl;i <= K;++i){
    u = seq[i]，fl = 0;
    for(int j = 0, v;j < e[u].size();++j){
      v = e[u][j];
      if(vis[v]){
    	fl = 1;break;
      }
    }
    if(!fl)ans++, vis[u] = 1;
  }
  return ans;
}
