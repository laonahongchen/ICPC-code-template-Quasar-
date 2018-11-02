//z[i]表示s[i..n-1]和s[0..n-1]的最长公共前缀
void exkmp(char *s, int n, int *z) {
	memset(z, 0, sizeof(z[0]) * n);
	for (int i = 1, x = 0, y = 0; i < n; ++i) {
		if (i <= y) z[i] = min(y - i, z[i - x]);
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if (y <= i + z[i]) x = i, y = i + z[i];
	}
	z[0] = n;
}
