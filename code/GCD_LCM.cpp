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
const int N = 1e9 + 7;
const int di[] = { -1,0,1,0 };
const int dj[] = { 0,1,0,-1 };

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
	return abs(a * b) / gcd(a, b);
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	cin.ignore(), cin.get();
}