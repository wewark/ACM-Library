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
const int di[] = { 0, 0, 1, -1 };
const int dj[] = { 1, -1, 0, 0 };
const ll MOD = 1e9 + 9;
const ll INF = 1e9;
const long double EPS = 1e-6;
#define all(x) x.begin(),x.end()

int n;
vvi adj;

vb vis;
map<pii, int> dist;
vi subTreeSize;
int subTreeSizeDFS(int node, int prnt, int start, int startDist = 1) {
	subTreeSize[node] = 1;
	dist[pii(node, start)] = dist[pii(start, node)] = startDist;
	for (auto& i : adj[node]) {
		if (i != prnt && !vis[i])
			subTreeSize[node] += subTreeSizeDFS(i, node, start, startDist + 1);
	}
	return subTreeSize[node];
}

int getCentroid(int node, int curPrnt) {
	int prv = -1;
	subTreeSizeDFS(node, -1, curPrnt);
	int sz = subTreeSize[node];
	for (int i = 0; i < (int)adj[node].size(); i++) {
		if (!vis[adj[node][i]] && adj[node][i] != prv &&
			subTreeSize[adj[node][i]] > sz / 2) {
			prv = node;
			node = adj[node][i];
			i = -1;
		}
	}
	return node;
}

vi prnt;
void decomposeCentroid() {
	vis.assign(n, false);
	prnt.assign(n, 0);
	subTreeSize.assign(n, 0);

	queue<pii> q;
	q.emplace(0, -1);

	while (!q.empty()) {
		int cur = q.front().first;
		int prvCent = q.front().second;
		q.pop();

		cur = getCentroid(cur, prvCent);
		prnt[cur] = prvCent;
		vis[cur] = true;

		for (auto& i : adj[cur]) {
			if (!vis[i]) {
				q.emplace(i, cur);
			}
		}
	}
}

// http://codeforces.com/contest/342/problem/E

vi mnRed;

void queryPaint(int node) {
	int cur = node;
	mnRed[node] = 0;
	while (~prnt[cur]) {
		cur = prnt[cur];
		mnRed[cur] = min(mnRed[cur], dist[pii(cur, node)]);
	}
}

int queryClosest(int node) {
	int cur = node;
	int ret = mnRed[node];
	while (~prnt[cur]) {
		cur = prnt[cur];
		ret = min(ret, mnRed[cur] + dist[pii(cur, node)]);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int m; cin >> n >> m;
	adj.assign(n, vi());
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	decomposeCentroid();

	mnRed.assign(n, INF);
	queryPaint(0);
	while (m--) {
		int t, v; cin >> t >> v; v--;
		if (t == 1) {
			queryPaint(v);
		}
		else {
			cout << queryClosest(v) << endl;
		}
	}
	cin.ignore(), cin.get();
}
