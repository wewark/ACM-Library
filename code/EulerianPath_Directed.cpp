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
const int di[] = { -1, 0, 1, 0 };
const int dj[] = { 0, 1, 0, -1 };
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const double EPS = 1e-5;
#define mp make_pair
#define all(x) x.begin(),x.end()

struct Edge;
typedef list<Edge>::iterator iter;

struct Edge
{
	int next_vertex;
	iter reverse_edge;

	Edge(int next_vertex)
		:next_vertex(next_vertex)
	{ }
};

const int max_vertices = 1e5 * 2 + 5;
int num_vertices;
list<Edge> adj[max_vertices];		// adjacency list
vi adjin, adjout;

vector<int> path;

void find_path(int v)
{
	while (adj[v].size() > 0)
	{
		int vn = adj[v].front().next_vertex;
		//adj[vn].erase(adj[v].front().reverse_edge);
		adj[v].pop_front();
		find_path(vn);
	}
	path.push_back(v);
}

void add_edge(int a, int b)
{
	//adj[a].push_front(Edge(b));
	//iter ita = adj[a].begin();
	adj[b].push_front(Edge(a));
	//iter itb = adj[b].begin();
	//ita->reverse_edge = itb;
	//itb->reverse_edge = ita;
	adjout[a]++, adjin[b]++;
}

map<string, int> cnt;

int find(vector<int> &C, int x) { return (C[x] == x) ? x : C[x] = find(C, C[x]); }
void merge(vector<int> &C, int x, int y) { C[find(C, x)] = find(C, y); }

bool connected(vi& C) {
	for (int i = 1; i < C.size(); i++)
		if (find(C, i) != find(C, 0))
			return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vs w(n);
	map<string, int> nd;
	vs str;
	int cn = 0;
	for (int i = 0; i < n; i++) {
		cin >> w[i];
		cnt[w[i]]++;
		string a = w[i].substr(0, 2);
		string b = w[i].substr(1);
		if (nd.find(a) == nd.end())
			nd[a] = cn++, str.push_back(a);
		if (nd.find(b) == nd.end())
			nd[b] = cn++, str.push_back(b);
	}

	vector<int> C(cn);
	for (int i = 0; i < cn; i++) C[i] = i;

	adjin.assign(cn, 0), adjout = adjin;
	for (int i = 0; i < n; i++) {
		string u = w[i].substr(0, 2);
		string v = w[i].substr(1);
		merge(C, nd[u], nd[v]);
		add_edge(nd[u], nd[v]);
	}


	vi ls, gt;
	int eq = 0, ot = 0;
	for (int i = 0; i < cn; i++) {
		if (adjin[i] == adjout[i]) eq++;
		else if (adjin[i] + 1 == adjout[i])
			ls.push_back(i);
		else if (adjin[i] == adjout[i] + 1)
			gt.push_back(i);
		else
			ot++;
	}

	bool yes = !ot && connected(C), edgeAdded = false;
	if (!(ls.empty() && gt.empty() || ls.size() == 1 && gt.size() == 1)) yes = false;
	if (ls.size() == 1 && gt.size() == 1)
		add_edge(gt[0], ls[0]), edgeAdded = true;

	if (!yes) cout << "NO\n";
	else {
		cout << "YES\n";
		find_path(0);
		if (edgeAdded && !(path[0] == ls[0] && path.back() == gt[0])) {
			int c = 0;
			while (!(path[c] == gt[0] && path[c + 1] == ls[0])) c++;
			c++;
			for (int i = 1; i < c; i++)
				path.push_back(path[i]);
			path.erase(path.begin(), path.begin() + c);
		}

		string s = str[path[0]].substr(0, 2);
		for (int i = 1; i < path.size(); i++)
			s.push_back(str[path[i]][1]);

		cout << s << endl;
	}

	cin.ignore(), cin.get();
}
