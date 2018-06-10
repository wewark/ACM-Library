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
const int MOD = 1e9 + 7;
const int di[] = { -1,0,1,0 };
const int dj[] = { 0,1,0,-1 };
#define INF 1000000000

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	//ofstream cout("output.txt");
	int t; cin >> t;
	while (t--) {
		int n, e, T; cin >> n >> e >> T;
		vector<vii> adj(n, vii());
		e--;
		int m; cin >> m;
		for (int i = 0; i < m; i++) {
			int u, v, w; cin >> u >> v >> w;
			u--, v--;
			adj[v].push_back(pii(u, w));
		}
		int r = 0;


		// Dijkstra
		vector<int> dist(n, INF); dist[e] = 0;
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		pq.push(pii(0, e));
		
		while (!pq.empty()) {
			pii front = pq.top(); pq.pop();
			int d = front.first, u = front.second;
			if (d > dist[u]) continue;

			for (int j = 0; j < adj[u].size(); j++) {
				pii v = adj[u][j];
				if (dist[u] + v.second < dist[v.first]) {
					dist[v.first] = dist[u] + v.second;
					pq.push(pii(dist[v.first], v.first));
				}
			}
		}
		for (int i = 0; i < n; i++)
			r += dist[i] <= T;
		cout << r << endl;
		if (t != 0)
			cout << endl;
	}
	//cin.ignore(), cin.get();
}
