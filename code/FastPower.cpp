int fastPow(int a, int p, int mod = MOD) {
    int sol = 1;
    while (p != 0) {
        if (p % 2 != 0) {
            sol = (1LL * sol * a) % mod;
        }
        a = (1LL * a * a) % mod;
        p /= 2;
    }
    return sol;
}
