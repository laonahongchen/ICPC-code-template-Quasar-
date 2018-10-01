//51nod约数个数和
const int Mo = 1e9 + 7;
const int N = 1e6 +  10;
const int inv2 = 500000004;

map<ll, ll> mp;
int cnt, notp[N], pri[N], mu[N], s[N];
void Prime(){
  mu[1] = 1;
  for(int i = 2;i < N;++i){
    if(!notp[i])pri[++cnt] = i, mu[i] = -1;
    for(int j = 1;i * pri[j] < N;++j){
      notp[i * pri[j]] = 1;
      if(i % pri[j] == 0){
	mu[i * pri[j]] = 0;
	break;
      }
      else mu[i * pri[j]] = -mu[i];
    }
  }
  for(int i = 1;i < N;++i){
    s[i] = (s[i - 1] + 1LL * i * mu[i]) % Mo;
  }
}
ll calc(ll l, ll r){
  return 1LL * (l + r) * (r - l + 1) % Mo * inv2 % Mo;
}
ll solve1(ll n){
  if(n < N)return (ll)s[n];
  if(mp.count(n))return mp[n];
  ll res = 1;
  for(ll i = 2, j;i <= n;i = j + 1){
    j = n / (n / i);
    res = (res - calc(i, j) * solve1(n / i)) % Mo;
  }
  return mp[n] = res;
}
ll solve2(ll n){
  ll p = 0, q = 0;
  for(ll i = 1, j;i <= n;i = j + 1){
    j = n / (n / i);
    p = (p + calc(i, j) % Mo * (n / i)) % Mo;
    q = (q + (j - i + 1) * (n / i) % Mo * (n / i + 1)) % Mo;
  }
  return p * q % Mo * inv2 % Mo;
}
int main(){
  Prime();
  ll n, ans = 0;
  scanf("%lld", &n);
  for(ll i = 1, j;i <= n;i = j + 1){
    j = n / (n / i);
    ans = (ans + (solve1(j) - solve1(i - 1)) * solve2(n / i)) % Mo;
  }
  ans = (ans % Mo + Mo) % Mo;
  printf("%lld\n", ans);
  return 0;
}

