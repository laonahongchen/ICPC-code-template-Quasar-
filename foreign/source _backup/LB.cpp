const int N = 65;

LL bin[N], bas[N];
int pos[N], num;

void add(long long x, int m)
{
	for(int j = m; j >= 0; j--)
		if((x & bin[j]) && pos[j])
			x ^= bas[pos[j]];
	if(x == 0)
		return;
	for(int j = m; j >= 0; j--)
		if(x & bin[j])
		{
			pos[j] = ++num;
			bas[num] = x;
			break;
		}
}

int work(long long *a, int n, int m)
{
	num = 0;
	memset(pos, 0, sizeof(pos));
	for(int i = 1; i <= n; i++)
		add(a[i], m);
	return num;
}

