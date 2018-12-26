struct segTree {
	int tree[N << 2];
	segTree() {
		memset(tree, 63, sizeof tree);
	}
	void upd(int node, int s, int e, int idx, int v) {
		if (s == e) {
			tree[node] = v;
			return;
		}
		int md = (s + e) >> 1;
		if (idx <= md)
			upd(node << 1, s, md, idx, v);
		else
			upd(node << 1 | 1, md + 1, e, idx, v);
		tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
	}
	int qry(int node, int s, int e, int l, int r) {
		if (r < s || e < l)
			return INT_MAX;
		if (l <= s && e <= r)
			return tree[node];
		int md = (s + e) >> 1;
		return min(qry(node << 1, s, md, l, r),
				qry(node << 1 | 1, md + 1, e, l, r));
	}
}
