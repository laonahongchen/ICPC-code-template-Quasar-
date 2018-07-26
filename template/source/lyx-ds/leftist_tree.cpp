int merge(int a, int b)
{
    if(a == 0) return b;
    if(b == 0) return a;
    if(v[a] < v[b]) swap(a, b);
    rc[a] = merge(rc[a], b);
    if(rc[a]) fa[rc[a]] = a;
    if(d[lc[a]] < d[rc[a]]) swap(lc[a], rc[a]);
    d[a] = rc[a] ? d[rc[a]] + 1 : 0;
    return a;
}
