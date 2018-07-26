inline bool turn_left(const Point &a, const Point &b, const Point &c) {
	return sgn(det(b - a, c - a)) >= 0;
}

void convex_hull(vector<Data> p, vector<Data> &res) {
	int n = (int)p.size(), cnt = 0;
	sort(p.begin(), p.end(), [&](const Data &a, const Data &b) {
			if(fabs(a.p.x - b.p.x) < eps) return a.p.y > b.p.y;
			return a.p.x < b.p.x; });
	res.clear();
	for(int i = 0; i < n; i++) {
		while(cnt > 1 && turn_left(res[cnt - 2].p, p[i].p, res[cnt - 1].p)) {
			cnt--;
			res.pop_back();
		}
		res.push_back(p[i]);
		++cnt;
	}
	int fixed = cnt;
	for(int i = n - 2; i >= 0; i--) {
		while(cnt > fixed && turn_left(res[cnt - 2].p, p[i].p, res[cnt - 1].p)) {
			--cnt;
			res.pop_back();
		}
		res.push_back(p[i]);
		++cnt;
	}
}
