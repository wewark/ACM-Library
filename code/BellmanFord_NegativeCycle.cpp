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
#define mp make_pair

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	//ofstream cout("output.txt");
	int t, tt = 0; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		vector<vii> adj(n);
		for (int i = 0; i < m; i++) {
			int u, v, w; cin >> u >> v >> w;
			adj[u].push_back(pii(v, w));
		}

		// Bellman Ford routine
		vi dist(n, INF); dist[0] = 0;
		for (int i = 0; i < n - 1; i++)  // relax all E edges V-1 times, overall O(VE)
			for (int u = 0; u < n; u++)                        // these two loops = O(E)
				for (int j = 0; j < (int)adj[u].size(); j++) {
					pii v = adj[u][j];        // we can record SP spanning here if needed
					dist[v.first] = min(dist[v.first], dist[u] + v.second);         // relax
				}

		bool hasNegativeCycle = false;
		for (int u = 0; u < n; u++)                          // one more pass to check
			for (int j = 0; j < (int)adj[u].size(); j++) {
				pii v = adj[u][j];
				if (dist[v.first] > dist[u] + v.second)                 // should be false
					hasNegativeCycle = true;     // but if true, then negative cycle exists!
			}
		cout << (hasNegativeCycle ? "possible" : "not possible") << endl;
	}
	cin.ignore(), cin.get();
}
