#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vii;
typedef vector<bool> vb;
typedef vector<string> vs;
const int MOD = 1e9 + 7;
const int di[] = { -1,0,1,0 };
const int dj[] = { 0,1,0,-1 };

ll fastPow(ll a, int p, int m) {
	if (p == 0)
		return 1;
	if (p % 2 == 1)
		return (a * fastPow(a, p - 1, m)) % m;
	ll c = fastPow(a, p / 2, m);
	return  (c * c) % m;
}

int a, b, l;
bool good(string s) {
	for (int i = 0; i < s.length(); i++)
		if (s[i] - '0' != a && s[i] - '0' != b)
			return false;
	return true;
}
int sum(int n, int m) {
	return n * a + m * b;
}
vi mem(1e6 + 1, -1);
ll fact(int n) {
	if (mem[n] != -1)
		return mem[n];
	return mem[n] = (n == l ? l : (n * fact(n + 1)) % MOD);
}
vi mem2(1e6 + 1, -1);
// https://www.quora.com/How-do-I-evaluate-A-B-mod-1000000007
ll fact2(int n) {
	if (mem2[n] != -1)
		return mem2[n];
	if (n == 0)
		return 1;
	return mem2[n] = (bigmod(n, MOD - 2, MOD) * fact2(n - 1)) % MOD;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> a >> b >> l;
	ll r = 0;
	for (int i = 0; i <= l / 4; i += 10000)
		fact2(i), fact(l - i);
	for (int i = 0; i <= l; i++) {
		if (good(to_string(sum(i, l - i)))) {
			if (i == l || i == 0) r++;
			else
			// r += 1st fact / 2nd faction
				r += (fact(max(i, l - i) + 1) * fact2(min(i, l - i))) % MOD;
		}
	}
	cout << r % MOD << endl;
	//cin.ignore(), cin.get();
}