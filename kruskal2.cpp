#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include<sstream>
#include<list>
#include<iomanip>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <bitset>
#include <cassert>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
const int INF = 1000000000;
const long long LINF = 3e18 + 7;
const int MAX_N = 50010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// https://atcoder.jp/contests/utpc2013/tasks/utpc2013_06
// https://www.utpc.jp/2013/slides/F.pdf


struct uftree {
	int cou;
	vector<int> parent;
	vector<int> rank;
	vector<int> _size;
	uftree(int n) {
		init(n);
	}
	void init(const int& n) {
		parent = vector<int>(n);
		rank = vector<int>(n, 0);
		_size = vector<int>(n, 1);
		cou = n;
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}
	int root(const int& i) {
		return parent[i] == i ? i : parent[i] = root(parent[i]);
	}
	bool same(const int& i, const int& j) {
		return root(i) == root(j);
	}
	void merge(int i, int j) {
		i = root(i); j = root(j);
		if (i == j)return;
		cou--;
		if (rank[i] >= rank[j]) {
			parent[j] = i;
			_size[i] += _size[j];
		}
		else {
			parent[i] = j;
			_size[j] += _size[i];
		}
		if (rank[i] == rank[j])rank[i]++;
		return;
	}
	int count() {
		return cou;
	}
	int unitsize(const int& i) {
		return _size[root(i)];
	}
};

typedef pair<int, int> pint;
typedef pair<int, pair<int, int> > ppint;

int N, M, Q;
vector<pint> qry;
int v[2010][2010];
vector<ppint> table[2010];
vector<ppint> mem;
vector<string> ans;

int main() {

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		v[x][y] = v[y][x] = z;
	}

	cin >> Q;
	for(int i = 0;i < Q;i++) {
		int x, y;
		cin >> x >> y;
		qry.push_back(pint(x, y));
	}
	
	uftree tree(N);
	for (int q = 0; q < Q; q++) {

		int x, y;
		x = tree.root(qry[q].first);
		y = tree.root(qry[q].second);

		mem.clear();
		vector<int> g1, g2;
		for (int i = 0; i < N; i++) {
			if (tree.same(i, x)) {
				g1.push_back(i);
			}
		}
		for (int i = 0; i < N; i++) {
			if (tree.same(i, y)) {
				g2.push_back(i);
			}
		}

		for (int i = 0; i < g1.size(); i++) {
			for (int j = 0; j < g2.size(); j++) {
				if (v[g1[i]][g2[j]] != 0) {
					mem.push_back(ppint(v[g1[i]][g2[j]], pint(g1[i], g2[j])));
				}
			}
		}

		for (int i = 0; i < table[x].size(); i++) {
			mem.push_back(table[x][i]);
		}
		for (int i = 0; i < table[y].size(); i++) {
			mem.push_back(table[y][i]);
		}

		sort(mem.begin(), mem.end());

		long long rec = 0;
		tree.merge(x, y);
		vector<ppint> res;
		int count = tree.unitsize(x);
		table[tree.root(x)].clear();

		uftree tr(N);

		for (int i = 0; i < mem.size(); i++) {
			ppint w = mem[i];
			if (tr.same(w.second.first, w.second.second)) {
				continue;
			}
			count--;
			tr.merge(w.second.first, w.second.second);
			table[tree.root(x)].push_back(w);

			rec += w.first;
			if (count == 1) {
				break;
			}
		}

		if (count > 1) {
			cout << "IMPOSSIBLE" << endl;
		}
		else {
			cout << rec << endl;
		}

	}
	
	return 0;
}