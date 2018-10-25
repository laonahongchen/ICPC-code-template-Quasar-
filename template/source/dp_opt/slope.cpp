//Hdu 3507 Print Article 
//根据小于或大于判断维护斜率递增还是递减。
//根据递增或递减判断答案取队首还是队尾。
int n, m, Q[maxn];
ll f[maxn], sum[maxn];
ll Calc(int j, int i){
	return f[j] + (sum[i] - sum[j]) * (sum[i] - sum[j]) + m;
}
double Slope(int j, int k){
	if(sum[j] == sum[k])return 1e20;
	return (double)(f[j] + 1.0 * sum[j] * sum[j] - f[k] - 1.0 * sum[k] * sum[k]) / (sum[j] - sum[k]);
}
void DP(){
	int h = 1, t = 0;
	Q[++t] = 0;
	for(int i = 1;i <= n;++i){
		while(h < t && Slope(Q[h], Q[h + 1]) <= 2.0 * sum[i])h++;
		f[i] = Calc(Q[h], i);
		while(h < t && Slope(Q[t - 1], Q[t]) >= Slope(Q[t], i))t--;
		Q[++t] = i;
	}
	printf("%lld\n", f[n]);
}

