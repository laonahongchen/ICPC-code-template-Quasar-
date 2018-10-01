void Manacher(int n){
    for(int i = n;i >= 1;--i){
        if(i & 1)str[i] = '#';
        else str[i] = str[i >> 1];
    }
    str[0] = '$';str[n + 1] = '*';
    for(int i = 1, mx = 0, pos = 0;i <= n;++i){
        d[i] = i < mx ? min(d[pos*2 - i], mx - i) : 1;
        while(str[i - d[i]] == str[i + d[i]])d[i]++;
        if(i + d[i] > mx)mx = i + d[i], pos = i;
    }
}
