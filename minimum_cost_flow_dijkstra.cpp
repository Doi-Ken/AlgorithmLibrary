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

// Minimum Cost Flow (Dijkstra)
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B&lang=ja
// 蟻本 p. 203
// 始点0, 終点V-1

int V, E, F;
struct edge { int to, cap, cost, rev; };
typedef pair<int, int> P;

vector<edge> G[MAX_N];
int h[MAX_N];
int dist[MAX_N];
int prevv[MAX_N], preve[MAX_N];

// from からtoへ向かう容量cap, コストcostの辺をグラフに追加する
void add_edge(int from, int to, int cap, int cost) {
	edge e1 = { to, cap, cost, G[to].size() };
	G[from].push_back(e1);
	edge e2 = { from, 0, -cost, G[from].size() - 1 };
	G[to].push_back(e2);
}

// sからtへの流量f最小費用流を求める
// 流せない場合は-1を返す
int min_cost_flow(int s, int t, int f) {
	int res = 0;
	fill(h, h + V, 0);
	while (f > 0) {
		// ダイクストラ法を用いてhを更新する
		priority_queue<P, vector<P>, greater<P> > que;
		fill(dist, dist + V, INF);
		dist[s] = 0;
		que.push(P(0, s));
		while (!que.empty()) {
			P p = que.top(); que.pop();
			int v = p.second;
			if (dist[v] < p.first) {
				continue;
			}
			for (int i = 0; i < G[v].size(); i++) {
				edge& e = G[v][i];
				if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
					dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
					prevv[e.to] = v;
					preve[e.to] = i;
					que.push(P(dist[e.to], e.to));
				}
			}
		}
		if (dist[t] == INF) {
			return -1;
		}
		for (int v = 0; v < V; v++) {
			h[v] += dist[v];
		}

		// s-t間最短路に沿って目一杯流す
		int d = f;
		for (int v = t; v != s; v = prevv[v]) {
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += (d * h[t]);
		for (int v = t; v != s; v = prevv[v]) {
			edge& e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}

	return res;

}

int main() {
	
	cin >> V >> E >> F;

	for (int i = 0; i < E; i++) {
		int u, v, cap, cost;
		cin >> u >> v >> cap >> cost;
		add_edge(u, v, cap, cost);
	}


	cout << min_cost_flow(0, V - 1, F) << endl;

	return 0;
}