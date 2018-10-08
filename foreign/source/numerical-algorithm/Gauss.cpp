void Gauss(){
	int r,k;
	for(int i=0;i<n;i++){
		r=i;
		for(int j=i+1;j<n;j++)
			if(fabs(A[j][i])>fabs(A[r][i]))r=j;
		if(r!=i)for(int j=0;j<=n;j++)swap(A[i][j],A[r][j]);
		for(int k=i+1;k<n;k++){
			double f=A[k][i]/A[i][i];
			for(int j=i;j<=n;j++)A[k][j]-=f*A[i][j];
		}
	}
	for(int i=n-1;i>=0;i--){
		for(int j=i+1;j<n;j++)
			A[i][n]-=A[j][n]*A[i][j];
		A[i][n]/=A[i][i];
	}
}
bool Gauss(){
	for(int i=1;i<=n;i++){
		int r=0;
		for(int j=i;j<=m;j++)
		if(a[j][i]){r=j;break;}
		if(!r)return 0;
		ans=max(ans,r);
		swap(a[i],a[r]);
		for(int j=i+1;j<=m;j++)
		if(a[j][i])a[j]^=a[i];
	}for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++)if(a[i][j])
		a[i][n+1]=a[i][n+1]^a[j][n+1];
	}return 1;
}
int Gauss(){//求秩
	int r,now=-1;
	int ans=0;
	for(int i = 0; i <n; i++){
		r = now + 1;
		for(int j = now + 1; j < m; j++)
			if(fabs(A[j][i]) > fabs(A[r][i]))			
				r = j;
		if (!sgn(A[r][i])) continue;
		ans++;
		now++;
		if(r != now)
			for(int j = 0; j < n; j++)
				swap(A[r][j], A[now][j]);
		for(int k = now + 1; k < m; k++){
			double t = A[k][i] / A[now][i];
			for(int j = 0; j < n; j++){
				A[k][j] -= t * A[now][j];
			}
		}
	}
	return ans;
}
