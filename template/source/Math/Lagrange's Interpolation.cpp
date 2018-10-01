void Init(){
  inv[0] = 1;
  for(int i = 1;i < maxn;++i)inv[i] = 1LL * i * inv[i - 1] % Mo;
  inv[maxn - 1] = Pow(inv[maxn - 1], Mo - 2);
  for(int i = maxn - 2;i >= 0;--i)inv[i] = 1LL * inv[i + 1] * (i + 1) % Mo;
  for(int i = 1;i < maxn;++i)f[0][i] = 1;
  for(int k = 1;k < maxn;++k){
    for(int i = 1;i < maxn;++i){
      f[k][i] = 1LL * f[k - 1][i] * i % Mo;
    }
  }
  for(int k = 0;k < maxn;++k){
    for(int i = 1;i < maxn;++i){
      f[k][i] = (f[k][i] + f[k][i - 1]) % Mo;
    }
  }
}
int calc(int nn, int k){
  if(nn < maxn)return f[k][nn];
  int tmp = 1, res = 0;
  for(int i = 1;i < k + 3;++i)tmp = 1LL * tmp * (nn - i) % Mo;
  for(int i = 1;i < k + 3;++i){
    res = (res + 1LL * tmp * Pow(nn - i, Mo - 2) % Mo * inv[i - 1] % Mo * inv[k + 2 - i] % Mo * ((k + 2 - i) & 1 ? -1 : 1) * f[k][i]) % Mo;
  }
  return (res + Mo) % Mo;
}
