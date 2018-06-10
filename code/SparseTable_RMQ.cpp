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
const int di[] = { -1,0,1,0 };
const int dj[] = { 0,1,0,-1 };
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
#define mp make_pair
#define all(x) x.begin(),x.end()

class SparseTable
{
private:
	vi A;
	vvi st; // Sparse Table (N * log(N))

public:
	SparseTable() {}
	SparseTable(const vi& _A) {
		build(_A);
	}
	
	void build(const vi& _A) {
		st.assign(_A.size(), vi(log2(_A.size()) + 1));
		A = _A;

		int i, j;
		// initialize st for the intervals with length 1
		for (i = 0; i < A.size(); i++)
			st[i][0] = i;
		//compute values from smaller to bigger intervals
		for (j = 1; (1 << j) <= A.size(); j++)
			for (i = 0; i + (1 << j) - 1 < A.size(); i++)
				if (A[st[i][j - 1]] < A[st[i + (1 << (j - 1))][j - 1]])
					st[i][j] = st[i][j - 1];
				else
					st[i][j] = st[i + (1 << (j - 1))][j - 1];
	}

	int rmq(int i, int j) {
		int k = log2(j - i + 1);
		if (A[st[i][k]] <= A[st[j - (1 << k) + 1][k]])
			return st[i][k];
		else
			return st[j - (1 << k) + 1][k];
	}
};


int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vi num(n);
	for (int i = 0; i < n; i++)
		cin >> num[i];
	SparseTable st(num);
	int q, i, j; cin >> q;
	while (q--) {
		cin >> i >> j;
		cout << num[st.rmq(i, j)] << endl;
	}
	cin.ignore(), cin.get();
}
