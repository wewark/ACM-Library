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
const int di[] = { -1,0,1,0,1,1,-1,-1 };
const int dj[] = { 0,1,0,-1,1,-1,1,-1 };
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
#define mp make_pair

vi prefixTable(const string &needle) {
	int m = needle.size();
	vi pi(m + 1);
	pi[0] = -1;
	for (int i = 0; i < m; ++i) {
		pi[i + 1] = pi[i];
		while (pi[i + 1] > -1 && needle[pi[i + 1]] != needle[i])
			pi[i + 1] = pi[pi[i + 1]];
		
		pi[i + 1]++;
	}
	return pi;
}

void kmp(const string &needle, const string &haystack) {
	vi pi = prefixTable(needle);
	int n = haystack.size(), m = needle.size();
	int seen = 0;
	for (int i = 0; i < n; ++i) {
		while (seen > -1 && needle[seen] != haystack[i])
			seen = pi[seen];
		
		if (++seen == m) {
			printf("%d\n", i - m + 1);
			seen = pi[m]; // There are no more characters in needle, so with the next input character let's try with the pi of the whole needle.
		}
	}
}

// http://www.spoj.com/problems/NHAY/
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n;
	while (cin >> n) {
		string a, b; cin >> a >> b;
		kmp(a, b);
	}
	//cin.ignore(), cin.get();
}
