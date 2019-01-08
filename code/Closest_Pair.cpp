struct Point {
	int x, y;
};

vector<Point> p;
ll dist(Point p_i, Point p_j) {
	return (p_i.x - p_j.x) * (p_i.x - p_j.x) + (p_i.y - p_j.y) * (p_i.y - p_j.y);
}

ll rec(int l, int r) {
	if(l == r) return INF;

	ll ret, mid = (l + r) >> 1;
	double d;
	ret = min(rec(l, mid), rec(mid + 1, r));
	d = sqrt(ret);

	vector<Point> c;
	for(int i = l; i <= r; i++)
		if(abs(p[i].x - p[mid].x) <= d)
			c.push_back(p[i]);

	sort(c.begin(), c.end(), [](Point a, Point b) {
		if(a.y == b.y) return a.x < b.x;
		return a.y < b.y;
	});

	for(int i = 0; i < c.size(); i++)
		for(int j = i + 1; j < c.size() && (c[j].y - c[i].y) <= d; j++) {
			ret = min(ret, dist(c[i], c[j]));
			d = sqrt(ret);
		}

	return ret;
}

int main() {
//	ios::sync_with_stdio(0), cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif

	int n; scanf("%d", &n);
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		int c; scanf("%d", &c);
		sum += c;
		p.push_back({i, sum});
	}
	printf("%lld\n", rec(0, n - 1));
}
