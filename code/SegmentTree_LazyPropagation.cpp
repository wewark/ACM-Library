#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<bool> vb;
typedef vector<string> vs;
const int di[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dj[] = { 0, 1, 0, -1, -1, 1, -1, 1 };
const ll MOD = 1e9;
const ll INF = 1e9;
const long double EPS = 1e-7;
#define all(x) x.begin(),x.end()

typedef vector<int> vi;

class SegmentTree {
private:
	vi st, A, lazy;
	int n;
	int left(int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }

	void build(int p, int L, int R) {
		if (L == R)
			st[p] = A[L];
		else {
			build(left(p), L, (L + R) / 2);
			build(right(p), (L + R) / 2 + 1, R);
			int p1 = st[left(p)], p2 = st[right(p)];
			st[p] = p1 + p2;
		}
	}

	int query(int p, int L, int R, int i, int j) {
		if (i > R || j < L) return 0; //-1; // current segment outside query range

		if (lazy[p]) {
			st[p] += lazy[p] * (R - L + 1);

			if (L != R) {
				lazy[left(p)] += lazy[p];
				lazy[right(p)] += lazy[p];
			}

			lazy[p] = 0;
		}

		if (L >= i && R <= j) return st[p];               // inside query range

		int p1 = query(left(p), L, (L + R) / 2, i, j);
		int p2 = query(right(p), (L + R) / 2 + 1, R, i, j);

		// if (p1 == -1) return p2;   // if we try to access segment outside query
		// if (p2 == -1) return p1;                               // same as above
		return p1 + p2;
	}

	int update(int p, int L, int R, int i, int j, int new_value) {
		if (lazy[p]) {
			st[p] += lazy[p] * (R - L + 1);
			
			if (L != R) {
				lazy[left(p)] += lazy[p];
				lazy[right(p)] += lazy[p];
			}

			lazy[p] = 0;
		}

		// if the current interval does not intersect 
		// the update interval, return this st node value!
		if (i > R || j < L)
			return st[p];

		if (i <= L && R <= j) { // Segment fully within range
			st[p] += new_value * (R - L + 1);

			if (L != R) {
				lazy[left(p)] += new_value;
				lazy[right(p)] += new_value;
			}

			return st[p];
		}

		int p1 = update(left(p), L, (L + R) / 2, i, j, new_value);
		int p2 = update(right(p), (L + R) / 2 + 1, R, i, j, new_value);

		return st[p] = p1 + p2;
	}

public:
	SegmentTree(const vi &_A) {
		A = _A; n = (int)A.size();
		st.assign(4 * n, 0);
		lazy = st;
		build(1, 0, n - 1);
	}

	int query(int i, int j) { return query(1, 0, n - 1, i, j); }   // overloading

	int update(int i, int j, int new_value) {
		return update(1, 0, n - 1, i, j, new_value);
	}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while (t--) {
		int n, q; cin >> n >> q;
		vi A(n, 0);
		SegmentTree seg(A);
		
		while (q--) {
			int tp, a, b;
			cin >> tp >> a >> b;
			a--, b--;
			if (tp == 0) {
				int v; cin >> v;
				seg.update(a, b, v);
			}
			else {
				cout << seg.query(a, b) << endl;
			}
		}
	}
	cin.ignore(), cin.get();
}
