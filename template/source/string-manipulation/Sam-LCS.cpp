struct Node{
	int len, fail;
	int To[30];
}T[N];
int Lst, Root, tot, ans;
char s[N];
int Len[N], Ans[N], Ord[N];
void Add(int x, int l){
	int Nt = ++tot, p = Lst;
	T[Nt].len = l;
	for (;p && !T[p].To[x]; p = T[p].fail) T[p].To[x] = Nt;
	if (!p) T[Nt].fail = Root; else
	if (T[T[p].To[x]].len == T[p].len + 1) T[Nt].fail = T[p].To[x];
	else{
		int q = ++tot, qt = T[p].To[x];
		T[q] = T[qt];
		T[q].len = T[p].len + 1;
		T[qt].fail = T[Nt].fail = q;
		for (;p && T[p].To[x] == qt; p = T[p].fail) T[p].To[x] = q;
	}
	Lst = Nt;
}
bool cmp(int a, int b){
	return T[a].len < T[b].len;
}
int main(){
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	ans = n;
	Root = tot = Lst = 1;
	for (int i = 1; i <= n; i++)
		Add(s[i] - 'a' + 1, i);
	for (int i = 1; i <= tot; i++)
		Ord[i] = i;
	sort(Ord + 1, Ord + tot + 1, cmp);
	for (int i = 1; i <= tot; i++)
		Ans[i] = T[i].len;
	bool flag = 0;
	while (scanf("%s", s + 1) != EOF){
		flag = 1;
		int n = strlen(s + 1);
		int p = Root, len = 0;
		for (int i = 1; i <= tot; i++) Len[i] = 0;
		for (int i = 1; i <= n; i++){
			int x = s[i] - 'a' + 1;
			if (T[p].To[x]) len++, p = T[p].To[x];
			else {
				while (p && !T[p].To[x]) p = T[p].fail;
				if (!p) p = Root, len = 0;
				else len = T[p].len + 1, p = T[p].To[x];
			}
			Len[p] = max(Len[p], len);
		}
		for (int i = tot; i >= 1; i--){
			int Cur = Ord[i];
			Ans[Cur] = min(Ans[Cur], Len[Cur]);
			if (Len[Cur] && T[Cur].fail)
				Len[T[Cur].fail] = T[T[Cur].fail].len;
		}
	}
	if (flag){
		ans = 0;
		for (int i = 1; i <= tot; i++){
			ans = max(ans, Ans[i]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
