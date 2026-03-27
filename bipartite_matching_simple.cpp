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

// Bipartite Matching (Simple)
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A&lang=ja
// 蟻本 p. 197


int V, E;
int X, Y;
vector<int> G[MAX_N];
int match[MAX_N];
bool used[MAX_N];

// uとvを結ぶ辺をグラフに追加する
void add_edge(int u, int v) {
	G[u].push_back(v);
	G[v].push_back(u);
}

// 増加パスをDFSで探す
bool dfs(int v) {
	used[v] = true;
	for (int i = 0; i < G[v].size(); i++) {
		int u = G[v][i];
		int w = match[u];
		if (w < 0 || !used[w] && dfs(w)) {
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}

int bipartite_matching() {
	int res = 0;
	memset(match, -1, sizeof(match));
	for (int v = 0; v < V; v++) {
		if (match[v] < 0) {
			memset(used, 0, sizeof(used));
			if (dfs(v)) {
				res++;
			}
		}
	}
	return res;
}

int main() {

	cin >> X >> Y >> E;
	V = X + Y;

	for (int i = 0; i < E; i++) {
		int u, v;
		cin >> u >> v;
		add_edge(u, X + v);
	}

	cout << bipartite_matching() << endl;

	return 0;
}