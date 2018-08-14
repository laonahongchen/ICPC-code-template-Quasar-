int Dcmp(const double &x){
	if(x > -eps && x < eps)return 0;
	return x > 0 ? 1 : -1;
}
Point operator + (const Point &a, const Point &b){
	return Point(a.x + b.x, a.y + b.y);
}
Point operator - (const Point &a, const Point &b){
	return Point(a.x - b.x, a.y - b.y);
}
Point operator * (const Point &a, const double &b){
	return Point(a.x * b, a.y * b);
}
Point operator / (const Point &a, const double &b){
	return Point(a.x / b, a.y / b);
}
double operator * (const Point &a, const Point &b){
	return a.x * b.x + a.y * b.y;
}
double operator ^ (const Point &a, const Point &b){
	return a.x * b.y - b.x * a.y;
}
//边AB，AC构成的平行四边形的有向面积 
double Cross(const Point &a, const Point &b, const Point &c){
	return (b - a) ^ (c - a);
}
//判断点在线段上 
bool Online(const Point &a, const Point &b, const Point &p){
	return ((b - a) ^ (p - a)) == 0 && ((a - p) * (b - p)) <= 0;
}
//判断线段的规范相交(return 1),非规范相交(return 2),不相交(return 0),并求出交点p。 
int Intersection(Point a, Point b, Point c, Point d, Point &p){
	double sa, sb, sc, sd;
	int da, db, dc, dd;
	da = Dcmp(sa = Cross(a, b, c));
	db = Dcmp(sb = Cross(a, b, d));
	dc = Dcmp(sc = Cross(c, d, a));
	dd = Dcmp(sd = Cross(c, d, d));
	//规范相交 
	if((da ^ db) == -2 && (dc ^ dd) == -2){
		p = Point((c.x * sb - d.x * sa) / (sb - sa), (c.y * sb - d.y * sa) / (sb - sa));
		return 1;
	}
	//不规范相交 
	if(da == 0 && Dcmp((a - c) * (b - c)) <= 0)return p = c, 2;
	if(db == 0 && Dcmp((a - d) * (b - d)) <= 0)return p = d, 2;
	if(dc == 0 && Dcmp((c - a) * (d - a)) <= 0)return p = a, 2;
	if(dd == 0 && Dcmp((c - b) * (d - b)) <= 0)return p = b, 2;
	return 0;//不相交 
}


