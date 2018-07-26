#include <bits/stdc++.h>
using namespace std;
const int N = 100100;
char s[N];
/*
int work1(int *a, int n){//输出最靠左的最小表示
	for(int i = 0; i < n; i++)
		a[i + n] = a[i];
	int pos = 0;
	for(int i = 1, k; i < n;){
		for(k = 0; k < n && a[pos + k] == a[i + k]; k++);
		if(k < n && a[i + k] < a[pos + k]){
			int t = pos;
			pos = i;
			i = max(i + 1, t + k + 1);
		}
		else{
			i += k + 1;
		}
	}
	return pos;
}

int work2(int *a, int n){//输出最靠右的最小表示,待验，谨慎使用
	for(int i = 0; i < n; i++)
		a[i + n] = a[i];
	int pos = 0;
	for(int i = 1, k; i < n;){
		for(k = 0; k < n && a[pos + k] == a[i + k]; k++);
		if(k == n){
			pos = i;
			i++;
			continue;
		}
		if(k < n && a[i + k] < a[pos + k]){
			int t = pos;
			pos = i;
			i = max(i + 1, t + k + 1);
		}
		else{
			i += k + 1;
		}
	}
	return pos;
}
*/
int getmin(char *s, int n){// 0-base
	int i = 0, j = 1, k = 0;
	while(i < n && j < n && k < n){
		int x = i + k;
		int y = j + k;
		if(x >= n) x -= n;
		if(y >= n) y -= n;
		if(s[x] == s[y])
			k++;
		else{
			if(s[x] > s[y]) 
				i += k + 1;
			else
				j += k + 1;
			if(i == j)
				j ++;
			k = 0;
		}
	}
	return min(i ,j);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d", &n);
		scanf("%s", s);
		printf("%d\n", getmin(s, n));
	}
}
