// Composite Simpsons
double integrate(double fr, double to, double (*f)(double), int n = 1e7) {
	double h = (to - fr) / n;
	double integral = f(fr);
	for (int i = 1; i < n / 2; i++) {
		integral += 2.0 * f(fr + i * 2 * h) + 4.0 * f(fr + (i * 2 - 1) * h);
	}
	return h * integral / 3.0;
}

double r1, r2;
double f(double z) {
	return sqrt((r1 * r1 - z * z) * (r2 * r2 - z * z));
}
