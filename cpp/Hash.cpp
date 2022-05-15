//////////////////////
*перед использованием*
Hasher h(s);
s = "#" + s;
*индексация с единицы*
//////////////////////

struct Hasher {
	const int mod1 = (int)1e9 + 7;
	const int mod2 = (int)1e9 + 123;
	const int pt1 = 249;
	const int pt2 = 947;
	int add(int x, int y, int mod) {
		return (x + y) % mod;
	}
	int mul(int x, int y, int mod) {
		return (1LL * x * y) % mod;
	}
	int sub(int x, int y, int mod) {
		return (x - y + mod) % mod;
	}
	int n;
	vector <int> h1, h2, p1, p2;
	Hasher(string& s) {
		n = s.size();
		h1.resize(n + 1);
		h2.resize(n + 1);
		p1.resize(n + 1);
		p2.resize(n + 1);
		p1[0] = p2[0] = 1;
		for (int i = 0; i < n; i++) {
			h1[i + 1] = add(mul(h1[i], pt1, mod1), s[i] - 'a' + 1, mod1); // изменить если алфавит другой
			h2[i + 1] = add(mul(h2[i], pt2, mod2), s[i] - 'a' + 1, mod2); // и здесь тоже
			p1[i + 1] = mul(p1[i], pt1, mod1);
			p2[i + 1] = mul(p2[i], pt2, mod2);
		}
	}
	pii get_hash(int pos, int len) {
		pii ret;
		ret.first = sub(h1[pos + len - 1], mul(h1[pos - 1], p1[len], mod1), mod1);
		ret.second = sub(h2[pos + len - 1], mul(h2[pos - 1], p2[len], mod2), mod2);
		return ret;
	}
};
