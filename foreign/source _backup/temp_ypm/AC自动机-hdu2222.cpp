#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
typedef long long LL;
typedef long double DD;
const int inf = 1e9;
const int mo= 1e9+7;
const int N = 5e5+10;
int n, cnt, fail[N], son[N][26], num[N];
char s[N << 1];
bool f[N];

inline void clear(int i){
	memset(son[i], 0, sizeof(son[i]));
	fail[i] = num[i] = 0;
	f[i] = 0;
}

void insert(char *s, int n){
	int now = 1;
	for(int i = 1; i <= n; i++){
		int c = s[i] - 'a';
		if(!son[now][c]){
			cnt++;
			clear(cnt);
			son[now][c] = cnt;
		}
		now = son[now][c];
	}
	num[now]++;
}

queue<int> Q;
void ACmatch(){//建立fail指针
	fail[1] = 0;
	Q.push(1);
	while(!Q.empty()){
		int now = Q.front();
		Q.pop();
		for(int i = 0; i < 26; i++)
			if(son[now][i]){
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
	
int main(){
	int T = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		cnt = 1;
		clear(1);
		for(int i = 0; i < 26; i++)
			son[0][i] = 1;
		int len = 0;
		for(int i = 1; i <= n; i++){
			scanf("%s", s + 1);
			len = strlen(s + 1);
			insert(s, len);
			memset(s,0,sizeof(char)*(len+ 2));
		}
		ACmatch();
		scanf("%s", s + 1);
		len = strlen(s + 1);
		int ans = 0;
		for(int now = 1, i = 1; i <= len; i++){
			int c = s[i] - 'a';
			now = son[now][c];
			for(int j = now; j; j = fail[j]){
				if(f[j])
					break;
				f[j] = 1;
				ans += num[j];
			}
			
		}
		printf("%d\n", ans);
	}
	return 0;
}
