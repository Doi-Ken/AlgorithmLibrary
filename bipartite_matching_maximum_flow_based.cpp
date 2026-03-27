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
const int MAX_N = 2000010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// Bipartite Matching (Maximum flow based)
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp
// 蟻本 p. 195
// 始点0, 終点V-1

int V, E;
int X, Y;
struct edge { int to, cap, rev; };

vector<edge> G[MAX_N];
int level[MAX_N];
int iter[MAX_N];

// from からtoへ向かう容量capの辺をグラフに追加する
void add_edge(int from, int to, int cap) {
	edge e1 = { to, cap, G[to].size() };
	G[from].push_back(e1);
	edge e2 = { from, 0, G[from].size() - 1 };
	G[to].push_back(e2);

}

// sからの最短距離をBFSで計算する
void bfs(int s) {
	memset(level, -1, sizeof(level));
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int v = que.front(); que.pop();
		for (int i = 0; i < G[v].size(); i++) {
			edge& e = G[v][i];
			if (e.cap > 0 && level[e.to] < 0) {
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}


// 増加パスをDFSで探す
int dfs(int v, int t, int f) {
	if (v == t) {
		return f;
	}

	for (int &i = iter[v]; i < G[v].size(); i++) {
		edge& e = G[v][i];
		if (e.cap > 0 && level[v] < level[e.to]) {
			int d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}


// sからtへの最大流を求める
int max_flow(int s, int t) {
	int flow = 0;
	while (true) {
		bfs(s);
		if (level[t] < 0) {
			return flow;
		}
		memset(iter, 0, sizeof(iter));
		int f;
		while ((f = dfs(s, t, INF)) > 0) {
			flow += f;
		}
	}
}

int main() {
	
	cin >> X >> Y >> E;
	V = X + Y + 2;

	for (int i = 0; i < E; i++) {
		int u, v, c;
		cin >> u >> v;
		add_edge(u, v + X, 1);
	}
	
	for (int i = 0; i < X; i++) {
		add_edge(X + Y, i, 1);
	}

	for (int i = 0; i < Y; i++) {
		add_edge(X + i, X + Y + 1, 1);
	}

	cout << max_flow(X + Y, X + Y + 1) << endl;

	return 0;
}