ll C[2705][2705];

void initC() {
	for (int i = 1; i < 2705; i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
		}
	}
}