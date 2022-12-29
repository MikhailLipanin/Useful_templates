struct Sparse {
	const int BIT = 30;
	vector <int> log;
	vector <vector <int>> sp;
	Sparse(vector <int>& a) {
		int n = a.size();
		sp.resize(BIT, vector <int>(n));
		for (int i = 0; i < n; i++) {
			sp[0][i] = a[i];
		}
		for (int bit = 0; bit < BIT - 1; bit++) {
			for (int i = 0; i + (1 << bit) * 2 - 1 < n; i++) {
				sp[bit + 1][i] = min(sp[bit][i], sp[bit][i + (1 << bit)]);
			}
		}
		log.resize(n + 1);
		for (int i = 2; i <= n; i++) {
			log[i] = log[i / 2] + 1;
		}
	}
	int get(int l, int r) {
		if (l > r) swap(l, r);
		int b = log[r - l + 1];
		r = r - (1 << b) + 1;
		return min(sp[b][l], sp[b][r]);
	}
};
