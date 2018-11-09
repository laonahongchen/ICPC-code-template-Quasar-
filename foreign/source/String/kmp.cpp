void Gnext(){
  for(int i = 2, j;a[i] != '\0';++i){
    j = nxt[i - 1];
    while(j && a[j + 1] != a[i])j = nxt[j];
    if(a[j + 1] == a[i])j++;
    nxt[i] = j;
  }
}
int MP(){
  int j = 0, res = 0;
  for(int i = 1;b[i] != '\0';++i){
    while(j && a[j + 1] != b[i])j = nxt[j];
    if(a[j + 1] == b[i])j++;
    if(a[j + 1] == '\0'){
      res++, j = nxt[j];
    }
  }
  return res;
}

