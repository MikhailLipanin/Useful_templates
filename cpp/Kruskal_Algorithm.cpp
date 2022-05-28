#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>
using namespace std;

struct Edge {
	int from, to, weight;
	bool operator< (Edge& e) {
		return this->weight < e.weight;
	}
};

struct DSU {
	vector <int> p;
	DSU() = default;
	DSU(int n) {
		p.resize(n);
		for (int i = 0; i < n; i++) {
			p[i] = i;
		}
	}
	bool unite(int a, int b) {
		a = find_par(a);
		b = find_par(b);
		if (a != b) {
			if (rand() & 1) swap(a, b);
			p[b] = a;
			return true;
		}
		return false;
	}
	int find_par(int a) {
		return p[a] == a ? a : p[a] = find_par(p[a]);
	}
};

class Kruskals_algorithm {
private:
	int edges_cnt;
	int vert_cnt;
	vector <Edge> edges;
	DSU dsu;
public:
	Kruskals_algorithm(vector <Edge> _edges, int _vert) {
		this->edges = _edges;
		this->edges_cnt = _edges.size();
		this->vert_cnt = _vert;
		this->dsu = DSU(_vert);
	}
	pair <int, vector <Edge>> exec() {
		int cost = 0;
		vector <Edge> edg;
		sort(edges.begin(), edges.end());
		for (int i = 0; i < edges_cnt; i++) {
			int from = edges[i].from, to = edges[i].to;
			int weight = edges[i].weight;
			int x = dsu.find_par(from);
			int y = dsu.find_par(to);
			if (x != y) {
				cost += weight;
				edg.push_back(edges[i]);
				dsu.unite(from, to);
			}
		}
		return { cost, edg };
	}
	bool isConnected() {
		int chk = dsu.find_par(0);
		for (int i = 1; i < vert_cnt; i++) {
			if (dsu.find_par(i) != chk)
				return false;
		}
		return true;
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	vector <Edge> ar;
	for (int i = 0; i < m; i++) {
		int v, u, w;
		cin >> v >> u >> w;
		Edge e;
		e.from = v;
		e.to = u;
		e.weight = w;
		ar.push_back(e);
	}
	Kruskals_algorithm f = Kruskals_algorithm(ar, n);
	auto now = f.exec();
	if (!f.isConnected()) {
		cout << "NON-CONNECTED";
		return 0;
	}
	cout << now.first << '\n';
	return 0;
}
