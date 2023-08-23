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
const int INF = 100000000;
const long long LINF = 3e18 + 7;
const int MAX_N = 500010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=jp

struct edge {
	int to;
	long long cost;
};

typedef pair<long long, int> P;
vector<edge> G[MAX_N];
long long dist[MAX_N];
int N;

void dfs1(int idx, int par = -1) {

	for (int i = 0; i < G[idx].size(); i++) {
		edge e = G[idx][i];
		if (e.to == par) {
			continue;
		}
		dfs1(e.to, idx);
		dist[idx] = max(dist[idx], dist[e.to] + e.cost);
	}
}

long long dfs2(int idx, long long d_par, int par = -1) {

	vector<P> d_child;
	d_child.push_back(P(0, -1));
	for (int i = 0; i < G[idx].size(); i++) {
		edge e = G[idx][i];
		if (e.to == par) {
			d_child.push_back(P(d_par + e.cost, e.to));
		}
		else {
			d_child.push_back(P(e.cost + dist[e.to], e.to));
		}
	}
	sort(d_child.rbegin(), d_child.rend());

	long long ret = d_child[0].first + d_child[1].first;

	for (int i = 0; i < G[idx].size(); i++) {
		edge e = G[idx][i];
		if (e.to == par) continue;
		ret = max(ret, dfs2(e.to, d_child[d_child[0].second == e.to].first, idx));
	}
	return ret;
}


int main() {

	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		long long w;
		cin >> a >> b >> w;
		edge e;
		e.to = b;
		e.cost = w;
		G[a].push_back(e);
		e.to = a;
		G[b].push_back(e);
	}

	dfs1(0, -1);

	cout << dfs2(0, 0, -1) << endl;

	return 0;
}