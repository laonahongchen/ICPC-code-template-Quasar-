//本质不同的回文子串的个数 = 自动机节点个数 - 2。 
//siz[x]表示x节点代表的回文串在整个字符串中的出现次数。  
void Init(){nodecnt = 1, T[0].len = 0, T[0].fail = 1, T[1].len = -1;}
int Extend(int p, int c, int len){
	for(;str[len - T[p].len - 1] != str[len];p = T[p].fail);
	if(!T[p].nx[c]){
		int np = ++nodecnt, x;
		for(x = T[p].fail;str[len - T[x].len - 1] != str[len];x = T[x].fail);
		T[np].fail = T[x].nx[c];
		T[p].nx[c] = np;
		T[np].len = T[p].len + 2;
	}
	T[T[p].nx[c]].siz++;
	return T[p].nx[c];
}Init();
for(int i = 1, last = 0;str[i] != '\0';++i) last = Extend(last, str[i] - 'a', i);