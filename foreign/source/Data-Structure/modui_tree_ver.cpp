// st[x]：进x的时间戳，ed[x]：出x的时间戳
// 对于询问(a, b), a是dfs序较小的点，如果a是b的父亲,相当于询问(st[a], st[b])
// 否则相当于询问(ed[a], st[b]) - lca(a,b)