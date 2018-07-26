#include <bits/stdc++.h>

inline int read()
{
	int x = 0; int f = 1, c = getchar();
	while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
	while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

template<typename T>
inline int size(T *o)
{
	return o == NULL ? 0 : o->sz;
}

struct Node
{
	Node *lc, *rc;
	int r, v, cnt, sz;

	Node() {}
	Node(int _v)
	{
		v = _v;
		sz = 0;
		cnt = 1;
		r = rand();
		lc = NULL;
		rc = NULL;
	}
	void update()
	{
		sz = cnt + size(lc) + size(rc);
	}
};

template<typename T>
inline void rotate_l(T *&o)
{
	T *k = o->rc;
	o->rc = k->lc;
	k->lc = o;
	o->update();
	k->update();
	o = k;
}

template<typename T>
inline void rotate_r(T *&o)
{
	T *k = o->lc;
	o->lc = k->rc;
	k->rc = o;
	o->update();
	k->update();
	o = k;
}

void insert(Node *&o, int v)
{
	if(o == NULL)
		o = new Node(v);
	else if(v < o->v)
	{
		insert(o->lc, v);
		if(o->lc->r < o->r)
			rotate_r(o);
	}
	else if(v > o->v)
	{
		insert(o->rc, v);
		if(o->rc->r < o->r)
			rotate_l(o);
	}
	else ++o->cnt;
	o->update();
}

void remove(Node *&o, int v)
{
	assert(o);
	if(v < o->v)
		remove(o->lc, v);
	else if(v > o->v)
		remove(o->rc, v);
	else if(o->cnt == 1)
	{
		if(o->lc == NULL)
		{
			Node *k = o;
			o = o->rc;
			delete k;
		}
		else if(o->rc == NULL)
		{
			Node *k = o;
			o = o->lc;
			delete k;
		}
		else
		{
			if(o->lc->r < o->rc->r)
			{
				rotate_l(o);
				remove(o->lc, v);
			}
			else
			{
				rotate_r(o);
				remove(o->rc, v);
			}
		}
	}
	else --o->cnt;
	if(o) o->update();
}

void merge(Node *&to, Node *from)
{
	if(from == NULL) return;
	merge(to, from->lc);
	for(int i = 0; i < from->cnt; ++i)
		insert(to, from->v);
	merge(to, from->rc);
}

void deltree(Node *&o)
{
	if(o == NULL) return;
	deltree(o->lc);
	deltree(o->rc);
	delete o;
	o = NULL;
}

int rank(Node *o, int v)
{
	if(o == NULL) return 0;
	if(v < o->v) return rank(o->lc, v);
	else if(v == o->v) return size(o->lc) + o->cnt;
	else return size(o->lc) + o->cnt + rank(o->rc, v);
}

struct TreapNode
{
	TreapNode *lc, *rc;
	int r, v, sz; Node *rt;

	TreapNode() {}
	TreapNode(int _v)
	{
		v = _v;
		r = rand();
		sz = 0;
		lc = NULL;
		rc = NULL;
		rt = NULL;
	}
	void update()
	{
		deltree(rt);
		insert(rt, v);
		if(lc) merge(rt, lc->rt);
		if(rc) merge(rt, rc->rt);
		sz = size(lc) + size(rc) + 1;
	}
} *root = NULL;

void insert(TreapNode *&o, int pos, int v)
{
	if(o == NULL)
	{
		o = new TreapNode(v);
		insert(o->rt, v);
	}
	else if(pos < size(o->lc) + 1)
	{
		insert(o->rt, v);
		insert(o->lc, pos, v);
		if(o->lc->r < o->r)
			rotate_r(o);
	}
	else
	{
		insert(o->rt, v);
		insert(o->rc, pos - size(o->lc) - 1, v);
		if(o->rc->r < o->r)
			rotate_l(o);
	}
	o->sz = size(o->lc) + size(o->rc) + 1;
}

int getv(TreapNode *o, int pos)
{
	int s = size(o->lc) + 1;
	if(pos == s) return o->v;
	else if(pos < s) return getv(o->lc, pos);
	else return getv(o->rc, pos - s);
}

template<typename T>
void print(const T *o)
{
	if(o == NULL) return;
	print(o->lc);
	printf("%d ", o->v);
	print(o->rc);
}

void change(TreapNode *o, int pos, int oldv, int newv)
{
	if(o == NULL) return;
	assert(o->rt);
	remove(o->rt, oldv);
	insert(o->rt, newv);
	int s = size(o->lc) + 1;
	if(pos < s)
		change(o->lc, pos, oldv, newv);
	else if(pos == s)
		o->v = newv;
	else
		change(o->rc, pos - s, oldv, newv);
}

std::vector<int> vals;
std::vector<Node*> nodes;

void getintervals(TreapNode *o, int l, int r)
{
	if(o == NULL) return;
	if(l <= 1 && r >= o->sz)
	{
		nodes.push_back(o->rt);
		return;
	}
	int pos = size(o->lc) + 1;
	if(l < pos) getintervals(o->lc, l, r);
	if(l <= pos && pos <= r) vals.push_back(o->v);
	if(r > pos) getintervals(o->rc, l - pos, r - pos);
}

int query(int l, int r, int k)
{
	vals.clear();
	nodes.clear();
	getintervals(root, l, r);
	int L = 0, R = 70000, ans;
	while(L <= R)
	{
		int M = (L + R) >> 1;
		
		int tot = 0;
		for(int i = 0; i < (int)vals.size(); ++i)
			if(vals[i] <= M)
				++tot;
		for(int i = 0; i < (int)nodes.size(); ++i)
			tot += rank(nodes[i], M);

		if(tot < k)
			L = M + 1;
		else
		{
			ans = M;
			R = M - 1;
		}
	}
	return ans;
}

int main()
{
	int n = read();
	for(int i = 1; i <= n; ++i)
		insert(root, i - 1, read());
	int q = read();
	int lastans = 0;
	while(q--)
	{
		int t = getchar();
		while(!isalpha(t))
			t = getchar();
		if(t == 'Q')
		{
			int l = read() ^ lastans;
			int r = read() ^ lastans;
			int k = read() ^ lastans;
			printf("%d\n", lastans = query(l, r, k));
		}
		else
		{
			int x = read() ^ lastans;
			int v = read() ^ lastans;
			if(t == 'M')
			{
				int oldv = getv(root, x);
				change(root, x, oldv, v);
			}
			else
				insert(root, x - 1, v);
		}
	}
	return 0;
}
