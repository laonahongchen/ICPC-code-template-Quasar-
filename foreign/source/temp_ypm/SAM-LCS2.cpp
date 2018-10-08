int main(){
	static char s[N];
	scanf("%s", s + 1);
	tot = 0; root = las = newNode();
	int n = strlen(s + 1);
	for(int i = 1;i <= n; i++)
		extend(s[i] - 'a');
	static int cnt[N], order[N << 1];
	memset(cnt, 0, sizeof(*cnt) * (n + 5));
	for(int i = 1; i <= tot; i++) cnt[node[i].len]++;
	for(int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
	for(int i = tot; i; i--) order[ cnt[node[i].len]-- ] = i;
	static int ANS[N << 1], dp[N << 1];
	memset(dp, 0, sizeof(*dp) * (tot + 5));
	for(int i = 1; i <= tot; i++) ANS[i] = node[i].len;
	while(scanf("%s", s + 1) == 1){
		n = strlen(s + 1);
		for(int now = root, len = 0, i = 1; i <= n; i++){
			int c = s[i] - 'a';
			while(now != root && !node[now].son[c]) now = node[now].par;
			if(node[now].son[c]){
				len = min(len, node[now].len) + 1;
				now = node[now].son[c];
			}
			else len = 0;
			dp[now] = max(dp[now], len);
		}
		for(int i = tot; i; i--){
			int now = order[i];
			dp[node[now].par] = max(dp[node[now].par], dp[now]);
			ANS[now] = min(ANS[now], dp[now]);
			dp[now] = 0;
		}
	}
	int ans = 0;
	for(int i = 1; i<= tot; i++) ans = max(ans, ANS[i]);
	printf("%d\n", ans);
}
