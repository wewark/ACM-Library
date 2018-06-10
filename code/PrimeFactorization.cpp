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
const int MOD = 10000005;
const int di[] = { -1,0,1,0 };
const int dj[] = { 0,1,0,-1 };

vb isprime;
bool prime(ll n) {
	for (ll i = 2; i * i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}
void sieve(int n) {
	isprime.assign(n, true);
	isprime[1] = false;
	for (ll i = 2; i <= n; i++)
		if (isprime[i])
			for (ll j = i * i; j <= n; j += i)
				isprime[j] = false;
}
vi primeFactorize(int n) {
	vi ret;
	while (n % 2 == 0) {
		ret.push_back(2);
		n /= 2;
	}
	for (int i = 3; i * i <= n; i += 2)
		while (n % i == 0)
			ret.push_back(i), n /= i;
	if (n > 2) ret.push_back(n);
	return ret;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	ll n; cin >> n;
	sieve(4e6);
	primeFactorize(n);
	//cin.ignore(), cin.get();
}