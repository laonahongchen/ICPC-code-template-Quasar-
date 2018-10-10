int Gauss(){//求秩
	int r,now=-1;
	int ans=0;
	for(int i = 0; i < n; i++){
		r = now + 1;
		for(int j = now + 1; j < m; j++)
			if(fabs(A[j][i]) > fabs(A[r][i])) r = j;
		if (!sgn(A[r][i])) continue;
		ans++, now++;
		if(r != now) for(int j = 0; j < n; j++) swap(A[r][j], A[now][j]);
		for(int k = now + 1; k < m; k++){
			double t = A[k][i] / A[now][i];
			for(int j = 0; j < n; j++)
				A[k][j] -= t * A[now][j];
		}
	}
	return ans;
}
