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

// Minimum Cost Flow (Bellman Ford)
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B&lang=ja
// 蟻本 p. 200
// 始点0, 終点V-1

int V, E, F;
struct edge { int to, cap, cost, rev; };

vector<edge> G[MAX_N];
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
	while (f > 0) {
		//ベルマンフォードにより、s-t間最短路を求める
		fill(dist, dist + V, INF);
		dist[s] = 0;
		bool update = true;
		while (update) {
			update = false;
			for (int v = 0; v < V; v++) {
				if (dist[v] == INF) {
					continue;
				}
				for (int i = 0; i < G[v].size(); i++) {
					edge& e = G[v][i];
					if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
						dist[e.to] = dist[v] + e.cost;
						prevv[e.to] = v;
						preve[e.to] = i;
						update = true;
					}
				}
			}
		}
		if (dist[t] == INF) {
			return -1;
		}

		// s-t間最短路に沿って目一杯流す。
		int d = f;
		for (int v = t; v != s; v = prevv[v]) {
			d = min(d, G[prevv[v]][preve[v]].cap);
		}

		f -= d;
		res += (d * dist[t]);
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