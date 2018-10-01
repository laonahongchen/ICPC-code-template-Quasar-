void Guass(int N){
    for(int i = 1, j, k;i <= N;++i){
        for(j = i + 1, k = i;j <= N;++j){
            if(fabs(A[j][i]) > fabs(A[i][i]))k = j;
        }
        j = k;
        if(i != j){
            for(k = 1;k <= N + 1;++k)swap(A[i][k], A[j][k]);
        }
        for(j = i + 1;j <= N;++j){
            double tmp = A[j][i] / A[i][i];
            for(int k = 1;k <= N + 1;++k)A[j][k] -= tmp * A[i][k];
        }
    }
    for(int i = N;i > 0;--i){
        for(int j = i + 1;j <= N;++j){
            A[i][N + 1] -= A[i][j] * A[j][N + 1];
        }
        A[i][N + 1] /= A[i][i];
    }
}
