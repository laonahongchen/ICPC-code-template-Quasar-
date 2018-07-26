#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int inf = 1e9;
const int N = 101010;
const int C = 26;

int tot, las, root;
struct Node
{
	int son[C], len, par, count;
	void clear()
	{
		memset(son, 0, sizeof(son));
		par = count = len = 0;
	}
}node[N << 1];


inline int newNode()
{
	node[++tot].clear();
	return tot;
}

void extend(int c)//传入转化为数字之后的字符，从0开始
{
	int p = las, np = newNode();
	las = np;
	node[np].len = node[p].len + 1;
	for(;p && !node[p].son[c]; p = node[p].par)
		node[p].son[c] = np;
	if(p == 0)
		node[np].par = root;
	else
	{
		int q = node[p].son[c];
		if(node[p].len + 1 == node[q].len)
			node[np].par = q;
		else
		{
			int nq = newNode();
			node[nq] = node[q];
			node[nq].len = node[p].len + 1;
			node[q].par = node[np].par = nq;
			for(;p && node[p].son[c] == q; p = node[p].par)
				node[p].son[c] = nq;
		}
	}
}


int main(){
	static char s[N];
	scanf("%s", s + 1);
	tot = 0;
	root = las = newNode();
	int n = strlen(s + 1);
	for(int i = 1;i <= n; i++)
		extend(s[i] - 'a');
	
	static int cnt[N], order[N << 1];
	memset(cnt, 0, sizeof(*cnt) * (n + 5));
	for(int i = 1; i <= tot; i++)
		cnt[node[i].len]++;
	for(int i = 1; i <= n; i++)
		cnt[i] += cnt[i - 1];
	for(int i = tot; i; i--)
		order[ cnt[node[i].len]-- ] = i;
	
	static int ANS[N << 1], dp[N << 1];
	memset(dp, 0, sizeof(*dp) * (tot + 5));
	for(int i = 1; i <= tot; i++)
		ANS[i] = node[i].len;
	while(scanf("%s", s + 1) == 1)
	{
		n = strlen(s + 1);
		for(int now = root, len = 0, i = 1; i <= n; i++)
		{
			int c = s[i] - 'a';
			while(now != root && !node[now].son[c])
				now = node[now].par;
			if(node[now].son[c])
			{
				len = min(len, node[now].len) + 1;
				now = node[now].son[c];
			}
			else
				len = 0;
			dp[now] = max(dp[now], len);
		}
		for(int i = tot; i; i--)
		{
			int now = order[i];
			dp[node[now].par] = max(dp[node[now].par], dp[now]);
			ANS[now] = min(ANS[now], dp[now]);
			dp[now] = 0;
		}
	}
	int ans = 0;
	for(int i = 1; i<= tot; i++)
		ans = max(ans, ANS[i]);
	printf("%d\n", ans);
}

