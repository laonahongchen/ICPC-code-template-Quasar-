int getmin(char *s, int n){// 0-base
	int i = 0, j = 1, k = 0;
	while(i < n && j < n && k < n){
		int x = i + k; if(x >= n) x -= n;
		int y = j + k; if(y >= n) y -= n;
		if(s[x] == s[y]) k++;
		else{
			if(s[x] > s[y]) i += k + 1;
			else j += k + 1;
			if(i == j) j++;
			k = 0;
		}
	}
	return min(i ,j);
}
