LL inv(LL a, LL p) {
    LL d, x, y;
    exgcd(a, p, d, x, y);
    return d == 1 ? (x + p) % p : -1;
}
