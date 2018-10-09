void Insert(){
  int p = 0;
  for(int i = 0, c;str[i] != '\0';++i){
    c = str[i] - 'a';
    if(!ch[p][c])ch[p][c] = ++nodecnt;
    p = ch[p][c];
  }
  val[p] = 1;
}
void Build(){
  int h = 1, t = 0, p, u;
  for(int c = 0;c < 26;++c){
    p = ch[0][c];
    if(p)fail[p] = 0, Q[++t] = p;
  }
  while(h <= t){
    u = Q[h++];
    for(int c = 0;c < 26;++c){
      p = ch[u][c];
      if(!p)ch[u][c] = ch[fail[u]][c];
      else{
    	fail[p] = ch[fail[u]][c];
    	Q[++t] = p;
      }
    }
  }
}
