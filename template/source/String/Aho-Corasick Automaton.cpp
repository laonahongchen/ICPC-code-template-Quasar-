/*
Aho-Corasick Automaton

解决"出现"问题的关键:若a出现在b中,那么a必定是b的前缀的后缀。
 
多次出现算多次： 
BZOJ2434 [NOI2011]阿狸的打字机
多次询问：串a在串b中出现了多少次。
考虑单次询问,将串b的每个前缀在fail树中对应的节点到根的路径+1,那么只需要求出串a在fail树中对应的节点被标记了多少次。
对于多次询问,只需要将询问按照b在打字机串中出现的顺序排序更新即可。

多次出现算一次： 
BZOJ2754 [SCOI2012]喵星球上的点名 
有两个字符串集合A,B，询问A中的每个串a被B中的多少个串b包含，询问B中的每个串b包含A中的多少个串a。 
对集合A中的串建立自动机： 
每个串a的答案就是该串在fail树中对应的节点的子树中出现了多少个b串的前缀(只需要在危险节点处标记),问题转化成经典的数颜色问题。 
每个串b的答案就是该串的所有前缀在fail树中对应的节点到根节点的路径上出现了多少个不同的串a,问题转化成树链的并。 
求出siz[x]表示节点x以及它的所有后缀中有多少个串a,将b所有前缀对应的节点按照dfs序统计即可。 
*/
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


