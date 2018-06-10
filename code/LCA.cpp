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
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const long double EPS = 1e-7;
#define all(x) x.begin(),x.end()

int n;
vi prnt, lvl;
vvi adj, P;

void initLCA() {
	//we initialize every element in P with -1
	P.assign(n, vi(ceil(log2(n)), -1));

	//the first ancestor of every node i is prnt[i]
	for (int i = 0; i < n; i++)
		P[i][0] = prnt[i];

	//bottom up dynamic programing
	for (int j = 1; 1 << j < n; j++)
		for (int i = 0; i < n; i++)
			if (P[i][j - 1] != -1)
				P[i][j] = P[P[i][j - 1]][j - 1];
}

int LCA(int p, int q) {
	//if p is situated on a higher level than q then we swap them
	if (lvl[p] < lvl[q])
		swap(p, q);

	//we compute the value of [log(lvl[p)]
	int log = 1;
	while (1 << log <= lvl[p]) log++;
	log--;

	//we find the ancestor of node p situated on the same level
	//with q using the values in P
	for (int i = log; i >= 0; i--)
		if (lvl[p] - (1 << i) >= lvl[q])
			p = P[p][i];

	if (p == q) return p;

	//we compute LCA(p, q) using the values in P
	for (int i = log; i >= 0; i--)
		if (P[p][i] != -1 && P[p][i] != P[q][i])
			p = P[p][i], q = P[q][i];
	//cout << p + 1 << " " << q + 1 << endl;
	return prnt[p];
}


void dfs(int node, int cprnt, int clvl) {
	prnt[node] = cprnt;
	lvl[node] = clvl;
	for (int i = 0; i < adj[node].size(); i++)
		if (adj[node][i] != cprnt)
			dfs(adj[node][i], node, clvl + 1);
}

////////////////////////

map<pii, int> cnt;
int st;
vvi LCAs;
vi dc;

void dfs2(int node) {
	int tmp = 0;
	for (int i = 0; i < adj[node].size(); i++) {
		if (adj[node][i] != prnt[node])
			dfs2(adj[node][i]);
		tmp += st;
		st = 0;
	}

	st = LCAs[node].size() + tmp;
	for (int i = 0; i < LCAs[node].size(); i++)
		dc[LCAs[node][i]]++;
	st -= dc[node];

	if (~prnt[node] && st) {
		if (cnt.find(pii(node, prnt[node])) != cnt.end())
			cnt[pii(node, prnt[node])] += st;
		else
			cnt[pii(prnt[node], node)] += st;
	}
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	adj.assign(n, vi());
	vii idx(n - 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
		idx[i] = pii(u, v);
		cnt[pii(u, v)] = 0;
	}

	prnt.assign(n, -1);
	lvl.assign(n, 0);
	dfs(0, -1, 0);
	initLCA();

	LCAs.assign(n, vi());
	dc.assign(n, 0);
	int q; cin >> q;
	while (q--) {
		int u, v; cin >> u >> v; u--, v--;
		int x = LCA(u, v);
		LCAs[u].push_back(x);
		LCAs[v].push_back(x);
	}

	dfs2(0);
	for (int i = 0; i < n - 1; i++) {
		cout << cnt[idx[i]] << " \n"[i == n - 2];
	}

	cin.ignore(), cin.get();
}