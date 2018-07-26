#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
using Heap = __gnu_pbds::priority_queue<int>;

/*
void erase(point_iterator)
void modify(point_iterator, const_reference)
void join(priority_queue &other)
*/

const int MAXN = 100005;

int n, m;
int a[MAXN];
int fa[MAXN];
Heap T[MAXN];

int getfa(int x)
{
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

void input()
{
	for(int i = 1; i <= n; i++)
		scanf("%d", a + i);
	for(int i = 1; i <= n; i++) {
		fa[i] = i;
		T[i].clear();
		T[i].push(a[i]);
	}
}

void solve() {
	scanf("%d", &m);
	for(int cc = 1; cc <= m; cc++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x = getfa(x); y = getfa(y);
		if(x == y) {
			puts("-1");
			continue;
		}
		int vx = T[x].top(); T[x].pop(); T[x].push(vx >> 1);
		int vy = T[y].top(); T[y].pop(); T[y].push(vy >> 1);
		if(vx < vy) swap(x, y);
		T[x].join(T[y]); fa[y] = x;
		printf("%d\n", T[x].top());
	}
}
