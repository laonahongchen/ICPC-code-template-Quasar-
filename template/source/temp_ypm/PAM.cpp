const int C = 26;
const int N = 301010;

char s[N];
int cnt, last;

struct Node
{
	int son[C], fail, size, len;
	void newNode(int l)
	{
		memset(son, 0, sizeof(son));
		fail = size = 0;
		len = l;
	}
}node[N];

void init()
{
	cnt = 2;
	node[1].newNode(0);//Even root
	node[2].newNode(-1);//Odd root
	last = 1;
	node[1].fail = 2;
	node[2].fail = 1;
}

void add(int c, int L)
{
	int p = last;
	while(s[L - node[p].len - 1] != s[L])
		p = node[p].fail;
	if(!node[p].son[c])
	{
		int q = ++cnt, &fq = node[q].fail;
		node[q].newNode(node[p].len + 2);
		fq = node[p].fail;
		while(s[L - node[fq].len - 1] != s[L])
			fq = node[fq].fail;
		fq = max(1, node[fq].son[c]);
		node[p].son[c] = q;
	}
	last = node[p].son[c];
	node[last].size++;
}

void calc()
{
	for(int i = cnt; i; i--)
		node[node[i].fail].size += node[i].size;
}

int main()
{
	scanf("%s", s + 1)
	int n = strlen(s + 1);
	s[0] = '$';
	init();
	for(int i = 1; i <= n; i++)
		add(s[i] - 'a', i);
	calc();
}
