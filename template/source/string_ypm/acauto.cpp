const int C = 26;
const int L = 1e5 + 5;
const int N = 5e5+10;
int n, root, cnt, fail[N], son[N][26], num[N];
char s[L];

inline int newNode()
{
	cnt++;
	memset(son[cnt], 0, sizeof(son[cnt]));
	fail[cnt] = num[cnt] = 0;
	return cnt;
}

void insert(char *s)
{
	int n = strlen(s + 1);
	int now = 1;
	for(int i = 1; i <= n; i++)
	{
		int c = s[i] - 'a';
		if(!son[now][c])
			son[now][c] = newNode();
		now = son[now][c];
	}
	num[now]++;
}


void getfail(){
	static queue<int> Q;
	fail[root] = 0;
	Q.push(root);
	while(!Q.empty())
	{
		int now = Q.front();
		Q.pop();
		for(int i = 0; i < C; i++)
			if(son[now][i])
			{
				Q.push(son[now][i]);
				int p = fail[now];
				while(!son[p][i])
					p = fail[p];
				fail[son[now][i]] = son[p][i];
			}
			else
				son[now][i] = son[fail[now]][i];
	}
}

int main()
{
	cnt = 0;
	root = newNode();
	scanf("%d", &n);
	for(int i = 0; i < C; i++)
		son[0][i] = 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", s + 1);
		insert(s);
	}
	getfail();
	return 0;
}
