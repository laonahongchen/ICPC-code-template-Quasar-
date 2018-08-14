//每次求有多少个数对(x,y)，满足a≤x≤b，c≤y≤d，且gcd(x,y) = k
int cnt = 0, pri[maxn], mu[maxn], sum[maxn];
bool flag[maxn];
void Prime(){
    mu[1] = 1;
    for(int i = 2;i < maxn;++i){
        if(!flag[i]){
            pri[++cnt] = i, mu[i] = -1;
        }
        for(int j = 1;j <= cnt && pri[j] * i < maxn;++j){
            flag[i * pri[j]]=1;
            if(i % pri[j] == 0){
                mu[i * pri[j]] = 0;
                break;
            }
            else mu[i * pri[j]] = -mu[i];
        }
    }
    for(int i = 1;i < maxn;++i)sum[i] = sum[i-1] + mu[i];
}
int solve(int n,int m){
    int res = 0;
    if(n > m)swap(n, m);
    for(int i = 1, j;i <= n;i = j + 1){
        j = min(n / (n / i), m / (m / i));
        res += (n / i) * (m / i) * (sum[j] - sum[i - 1]);
    }
	return res;
}
int main(){
    Prime();
    int sumt=0;scanf("%d",&sumt);
    int A, B, C, D, P;
    while(sumt--){
    	scanf("%d%d%d%d%d", &C, &A, &D, &B, &P);
        int ans=solve(A / P , B / P );
        ans+=solve((C - 1) / P, (D - 1) / P);
        ans-=solve(A / P , (D - 1) / P );
        ans-=solve((C - 1) / P , B / P);
        printf("%d\n", ans);
    }
    return 0; 
}
