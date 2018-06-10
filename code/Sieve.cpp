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

vb isprime(4e6 + 1, true);
bool prime(ll n) {
	for (ll i = 2; i * i <= n; i++)
		if (n % i == 0)
			return false;
	return true;
}
void sieve(int n) {
	for (ll i = 2; i <= n; i++)
		if (isprime[i])
			for (ll j = i * i; j <= n; j += i)
				isprime[j] = false;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	sieve(4e6);
	//cin.ignore(), cin.get();
}