void manacher(char *st){
	static char s[N << 1]; 
	static int p[N << 1];
	int n = strlen(st + 1);
	s[0] = '$'; s[1] = '#';
	for(int i = 1; i <= n; i++)
		s[i << 1] = st[i], s[(i << 1) + 1] = '#';
	s[(n = n * 2 + 1) + 1] = 0;
	int pos, mx = 0, res = 0;
	for(int i = 1; i <= n; i++){
		p[i] = (mx > i) ? min(p[pos * 2 - i], mx - i) : 1;
		while(s[i + p[i]] == s[i - p[i]]) p[i]++;
		if(p[i] + i - 1 > mx) mx = p[i] + i - 1, pos = i;
	}
}
