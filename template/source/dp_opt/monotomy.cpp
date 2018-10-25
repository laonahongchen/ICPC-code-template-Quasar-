//Decision Monotony 
//分治写法
ll Calc(int j, int i){
  return f[la][j] + A[j] * (A[i] - A[j]);
}
void solve(int l, int r, int pl, int pr){
  if(l > r)return;
  int mid = (l + r) >> 1, pm = pr;
  f[no][mid] = -inf;
  for(int i = pl;i <= pr && i < mid;++i){
    if(Calc(i, mid) > f[no][mid]){
      f[no][mid] = Calc(i, mid);
      pm = i;
    }
  }
  solve(l, mid - 1, pl, pm);
  solve(mid + 1, r, pm, pr);
}

//二分写法
ll Calc(int fl, int j, int i){
  return f[fl][j] + A[j] * (A[i] - A[j]);
}
void solve(){
  int la = 1, no = 0;
  for(int k = 1;k <= K;++k){
    int h = 1, t = 0;
    la ^= 1, no ^= 1;
    Q[++t] = Node(k, k + 1, n);
    for(int i = k + 1;i <= n;++i){
      if(h <= t && Q[h].l > Q[h].r)h++;
      Q[h].l++;
      f[no][i] = Calc(la, Q[h].p, i);
      if(h <= t && Calc(la, i, n) <= Calc(la, Q[h].p, n))continue;
      while(h <= t && Calc(la, i, Q[t].l) >= Calc(la, Q[t].p, Q[t].l))t--;
      if(h <= t){
        int l = Q[t].l, r = Q[t].r, mid;
        while(l <= r){
          mid = (l + r) >> 1;
          if(Calc(la, i, mid) > Calc(la, Q[t].p, mid))r = mid - 1;
          else l = mid + 1;
        }
        Q[t].r = l - 1;
        Q[++t] = Node(i, l, n);
      }
      else Q[++t] = Node(i, i + 1, n);
    }
  }
  printf("%lld\n", f[no][n]);
}
