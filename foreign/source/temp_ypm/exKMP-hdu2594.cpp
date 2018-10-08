//nex[i]表示s和其后缀s[i, n]的lcp的长度
void getnext(char s[], int n, int nex[]){
	nex[1] = n;
	int &t = nex[2] = 0;
	for(; t + 2 <= n && s[1 + t] == s[2 + t]; t++);
	int pos = 2;
	for(int i = 3; i <= n; i++){
		if(i + nex[i - pos + 1] < pos + nex[pos]) nex[i] = nex[i - pos + 1];
		else{
			int j = max(0, nex[pos] + pos - i);
			for(;i + j <= n && s[i + j] == s[j + 1]; j++);
			nex[i] = j; pos = i;
		}
	}
}
//extend[i]表示s2和s1后缀s1[i, n]的lcp的长度
void getextend(char s1[], char s2[], int extend[]){
	int n = strlen(s1 + 1), m = strlen(s2 + 1);
	getnext(s2, m, next);
	int &t = extend[1] = 0, pos = 1;
	for(; t < n && t < m && s1[1 + t] == s2[1 + t]; t++);
	for(int i = 2; i <= n; i++){
		if(i + nex[i - pos + 1] < pos + extend[pos]) extend[i] = nex[i - pos + 1];
		else{
			int j = max(0, extend[pos] + pos - i);
			for(; i + j <= n && j < m && s1[i + j] == s2[j + 1]; j++);
			extend[i] = j; pos = i;
		}
	}
}
