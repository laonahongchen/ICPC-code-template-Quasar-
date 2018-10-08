//SAM利用后缀树进行计算，由儿子向parert更新
void extend(int c);//传入转化为数字之后的字符，从0开始
int main(){
	static char s[N];
	while(scanf("%s", s + 1) == 1){
		tot = 0;
		root = las = newNode();
		int n = strlen(s + 1);
		for(int i = 1;i <= n; i++) extend(s[i] - 'a');
		static int cnt[N], order[N << 1];
		memset(cnt, 0, sizeof(*cnt) * (n + 5));
		for(int  i = 1; i <= tot; i++) cnt[node[i].len]++;
		for(int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
		for(int i = tot; i; i--) order[ cnt[node[i].len]-- ] = i;
		static int dp[N]; memset(dp, 0, sizeof(dp));
		//dp[i]为长度为i的子串中出现次数最多的串的出现次数
		for(int now = root, i = 1;  i <= n; i++){
			now = node[now].son[s[i] - 'a'];
			node[now].count++;
		}
		for(int i = tot; i; i--){
			Node &now = node[order[i]];
			dp[now.len] = max(dp[now.len], now.count);
			node[now.par].count += now.count;
		}
		for(int i = n - 1; i; i--) dp[i] = max(dp[i], dp[i + 1]);
		for(int i = 1; i <= n; i++) printf("%d\n", dp[i]);
	}
}
