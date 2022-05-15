#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <stack>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <random>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <complex>
#include <ctime>
#include <numeric>
using namespace std;

bool cmp(const vector <int>& a, const vector <int>& b) {
	if (a.size() != b.size())
		return a.size() < b.size();
	for (int i = (int)a.size() - 1; i >= 0; i--) {
		if (a[i] != b[i])
			return a[i] < b[i];
	}
	return false;
}
vector <int> sum(const vector <int>& a, const vector <int>& b) {
	int i = 0, s = 0;
	vector <int> res;
	while (i < (int)a.size() || i < (int)b.size()) {
		if (i < (int)a.size())
			s += a[i];
		if (i < (int)b.size())
			s += b[i];
		i++;
		res.push_back(s % 10);
		s /= 10;
	}
	if (s != 0)
		res.push_back(s);
	return res;
}
vector <int> diff(const vector <int>& a, const vector <int>& b) {
	int i = 0, s = 0, q = 0;
	vector <int> res;
	while (i < (int)a.size() || i < (int)b.size()) {
		s = 0;
		if (i < (int)a.size())
			s += a[i];
		if (i < (int)b.size())
			s -= b[i];
		s -= q;
		if (s < 0) {
			s += 10;
			q = 1;
		}
		else q = 0;
		res.push_back(s % 10);
		i++;
	}
	return res;
}

class longint {
private:
	vector <int> num;
	int sign;
	void normalize() {
		while (num.size() > 1 && num.back() == 0) num.pop_back();
		if (num.size() == 1 && num.back() == 0) sign = 1;
	}
public:
	longint(string s = "0") {
		if (s.size() == 0) {
			num.push_back(0);
			sign = 1;
			return;
		}
		if (s[0] == '-') sign = -1;
		else sign = 1;
		for (int i = (int)s.size() - 1; i >= 0 + (sign == -1); i--)
			num.push_back(s[i] - '0');
		normalize();
	}
	string to_string() const {
		string res;
		if (sign == -1)
			res.push_back('-');
		for (int i = (int)num.size() - 1; i >= 0; i--)
			res.push_back(num[i] + '0');
		return res;
	}
	bool operator < (const longint& l) const {
		if (sign * l.sign == -1)
			return sign < l.sign;
		if (sign > 0 && cmp(num, l.num))
			return true;
		if (sign < 0 && cmp(l.num, num))
			return true;
		return false;
	}
	bool operator > (const longint& l) const {
		return l < *this;
	}
	longint operator + (const longint& l) const {
		if (sign * l.sign == 1) {
			longint res;
			res.sign = sign;
			res.num = sum(num, l.num);
			res.normalize();
			return res;
		}
		else {
			if (cmp(num, l.num)) {
				longint res;
				res.sign = l.sign;
				res.num = diff(l.num, num);
				res.normalize();
				return res;
			}
			else {
				longint res;
				res.sign = sign;
				res.num = diff(num, l.num);
				res.normalize();
				return res;
			}
		}
	}
	longint operator - (const longint& l) const {
		longint res = l;
		res.sign *= -1;
		return *this + res;
	}
};

istream& operator >> (istream& in, longint& l) {
	string s;
	in >> s;
	l = longint(s);
	return in;
}
ostream& operator << (ostream& out, const longint& l) {
	out << l.to_string();
	return out;
}

int main() {
	longint a, b;
	cin >> a >> b;
	cout << a - b;
	return 0;
}
