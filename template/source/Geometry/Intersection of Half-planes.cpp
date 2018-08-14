Intersection of Half-planes
struct Line{
	Point p, v;
	double ang;
	Line(){;}
	Line(Point a, Point b){
		p = a;v = b - a;ang = atan2(v.y, v.x);
	}
}lines[maxn], Q[maxn];
bool operator < (const Line &a, const Line &b){
	return a.ang < b.ang;
}
Point Intersection(const Line &a, const Line &b){
	return a.p + a.v * (Cross(b.v, a.p - b.p) / Cross(a.v, b.v));
}
bool Onleft(const Point &a, const Line &b){
	return Dcmp(Cross(b.v, a - b.p)) >= 0;
}
void HalfIntersection(int n){
	int h = 1, t = 0;
	sort(lines + 1, lines + n + 1);
	for(int i = 1;i <= n;++i){
		while(h < t && !Onleft(poi[t - 1], lines[i]))t--;
		while(h < t && !Onleft(poi[h], lines[i]))h++;
		if(h <= t && Dcmp(Cross(lines[i].v, Q[t].v)) == 0){
			Q[t] = Onleft(lines[i].p, Q[t]) ? lines[i] : Q[t];
		}
		else Q[++t] = lines[i];	
		if(h < t)poi[t - 1] = Intersection(Q[t - 1], Q[t]);
	}
	while(h < t && !Onleft(poi[t - 1], Q[h]))t--;
	double ans = 0;
	poi[t] = Intersection(Q[h], Q[t]);
	for(int i = h + 1;i < t;++i){
		ans += Cross(poi[i] - poi[h], poi[i + 1] - poi[h]);
	}
	ans /= 2.0;//封闭平面的面积 
	printf("%.10lf\n", ans);
	//可形成封闭平面的条件：t - h + 1 >= 3 
}
 
