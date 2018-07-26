#include <bits/stdc++.h>

using namespace std;

inline int read()
{
	int x = 0; int f = 1, c = getchar();
	while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
	while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

inline char Getchar()
{
	char t = getchar();
	while(!isalpha(t))
		t = getchar();
	return t;
}

typedef unsigned long long hash_t;

const int N = 100005;
const int base = 233;

hash_t pw[N];

void init()
{
	pw[0] = 1;
	for(int i = 1; i <= 100000; i++)
		pw[i] = pw[i - 1] * base;
}


struct Node
{
	Node *lc, *rc;
	int sz;
	char c;
	hash_t h;
	bool rev;
	int add;
	int mn;
	int val;

	void update();
	void pushdown();
} nodepool[N], *pool = nodepool, *root = NULL;

#define idx(c) (c - 'a' + 1)
#define sz(x) (x == NULL ? 0 : x->sz)
#define hash(x) (x == NULL ? 0 : x->h)

Node *newnode(char c)
{
	Node *o = pool++;
	o->lc = o->rc = NULL;
	o->sz = 1;
	o->c = c;
	o->h = idx(c);
	return o;
}

void Node::pushdown()
{
	if(rev) {
		if(lc != NULL) {
			lc->rev ^= 1;
			swap(lc->lc, lc->rc);
		}
		if(rc != NULL) {
			rc->rev ^= 1;
			swap(rc->lc, rc->rc);
		}
		rev = 0;
	}
	if(add) {
		if(lc != NULL) {
			lc->add += add;
			lc->val += add;
			lc->mn += add;
		}
		if(rc != NULL) {
			rc->add += add;
			rc->val += add;
			rc->mn += add;
		}
		add = 0;
	}
}

void Node::update()
{
	sz = sz(lc) + sz(rc) + 1;
	h = hash(lc) * pw[sz(rc) + 1] + idx(c) * pw[sz(rc)] + hash(rc);
}

void split(Node *o, int k, Node *&l, Node *&r)
{
//	if(o) o->pushdown();
	if(k == 0) l = NULL, r = o;
	else if(k == sz(o)) l = o, r = NULL;
	else if(k <= sz(o->lc)) r = o, split(o->lc, k, l, r->lc), r->update();
	else l = o, split(o->rc, k - sz(o->lc) - 1, l->rc, r), l->update();
}

inline int r()
{
	static int s = 3023192386;
	return (s += (s << 3) + 1) & (~0u >> 1);
}

bool rand_cmp(int x, int y)
{
	return r() % (x + y) < x;
}

Node *merge(Node *x, Node *y)
{
	if(x == NULL) return y;
	if(y == NULL) return x;
//	x->pushdown();
//	y->pushdown();
	if(rand_cmp(x->sz, y->sz))
	{
		x->rc = merge(x->rc, y);
		x->update(); return x;
	}
	else
	{
		y->lc = merge(x, y->lc);
		y->update(); return y;
	}
}

void insert(int pos, char c)
{
	Node *l, *r;
	split(root, pos, l, r);
	root = merge(merge(l, newnode(c)), r);
}

void change(int pos, char c)
{
	Node *l, *r, *o;
	split(root, pos - 1, l, r);
	split(r, 1, o, r);
	o->c = c; o->update();
	root = merge(merge(l, o), r);
}

hash_t gethash(int l, int r)
{
	if(l > r) return 0;
	Node *x, *y, *o;
	split(root, r, x, y);
	split(x, l - 1, x, o);
	hash_t res = o->h;
	root = merge(merge(x, o), y);
	return res;
}

int getlcp(int x, int y)
{
	int l = 0, res = 0;
	int r = std::min(sz(root) - x + 1, sz(root) - y + 1);
	while(l <= r)
	{
		int mid = (l + r) >> 1;
	if(gethash(x, x + mid - 1) == gethash(y, y + mid - 1))
			l = mid + 1, res = mid;
		else
			r = mid - 1;
	}
	return res;
}

void solve()
{
	static char s[N];
	scanf("%s", s + 1);

	int len = 0;
	for(int i = 1; s[i]; i++)
		insert(len++, s[i]);

	int q = read();
	while(q--)
	{
		char t = Getchar();
		if(t == 'Q')
		{
			int x = read(), y = read();
			printf("%d\n", getlcp(x, y));
		}
		else if(t == 'R')
		{
			int x = read();
			char c = Getchar();
			change(x, c);
		}
		else
		{
			int x = read();
			char c = Getchar();
			insert(x, c);
		}
	}
}

int main()
{
	init();
	solve();
	return 0;
}
