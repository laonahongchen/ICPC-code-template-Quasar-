//SAM利用后缀树进行计算，由儿子向parert更新
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int inf = 1e9;
const int N = 251010;
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
	while(scanf("%s", s + 1) == 1)
	{
		tot = 0;
		root = las = newNode();
		int n = strlen(s + 1);
		for(int i = 1;i <= n; i++)
			extend(s[i] - 'a');
		
		static int cnt[N], order[N << 1];
		memset(cnt, 0, sizeof(*cnt) * (n + 5));
		for(int  i = 1; i <= tot; i++)
			cnt[node[i].len]++;
		for(int i = 1; i <= n; i++)
			cnt[i] += cnt[i - 1];
		for(int i = tot; i; i--)
			order[ cnt[node[i].len]-- ] = i;
		
		static int dp[N];//dp[i]为长度为i的子串中出现次数最多的串的出现次数
		memset(dp, 0, sizeof(dp));
		for(int now = root, i = 1;  i <= n; i++)
		{
			now = node[now].son[s[i] - 'a'];
			node[now].count++;
		}
		for(int i = tot; i; i--)
		{
			Node &now = node[order[i]];
			dp[now.len] = max(dp[now.len], now.count);
			node[now.par].count += now.count;
		}
		for(int i = n - 1; i; i--)
			dp[i] = max(dp[i], dp[i + 1]);
		for(int i = 1; i <= n; i++)
			printf("%d\n", dp[i]);
	}
}
