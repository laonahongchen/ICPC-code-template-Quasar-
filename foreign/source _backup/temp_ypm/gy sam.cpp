const int N = 251010, C = 26;
int tot, las, root;
struct Node
{
	int son[C], len, par;
	void clear(){
		memset(son, 0, sizeof(son));
		par = len = 0;
	}
}node[N << 1];
inline int newNode(){return node[++tot].clear(), tot;}
void extend(int c) 
{
	int p = las;
	if (node[p].son[c]) {
		int q = node[p].son[c];
		if (node[p].len + 1 == node[q].len)	las = q;
		else{
			int nq = newNode(); 
			las = nq; node[nq] = node[q];
			node[nq].len = node[p].len + 1;	node[q].par = nq;
			for (; p && node[p].son[c] == q; p = node[p].par)
				node[p].son[c] = nq;
		}
	}
	else{ // Naive Suffix Automaton
		int np = newNode();
		las = np; node[np].len = node[p].len + 1;
		for (; p && !node[p].son[c]; p = node[p].par)
			node[p].son[c] = np;
		if (!p) node[np].par = root;
		else{
			int q = node[p].son[c];
			if (node[p].len + 1 == node[q].len)
				node[np].par = q;
			else{
				int nq = newNode();
				node[nq] = node[q];
				node[nq].len = node[p].len + 1;
				node[q].par = node[np].par = nq;
				for (; p && node[p].son[c] == q; p = node[p].par)
					node[p].son[c] = nq;
			}
		}
	}
}
void add(char *s)
{
	int len = strlen(s + 1); las = root;
	for(int i = 1; i <= len; i++) extend(s[i] - 'a');
}
