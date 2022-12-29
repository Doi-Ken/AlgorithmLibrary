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

// Maximum Flow (Fold-Fulkerson)
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp
// �a�{ p. 190
// �n�_0, �I�_V-1

int V, E;
struct edge { int to, cap, rev; };

vector<edge> G[MAX_N];
bool used[MAX_N];

// from ����to�֌������e��cap�̕ӂ��O���t�ɒǉ�����
void add_edge(int from, int to, int cap) {
	edge e1 = { to, cap, G[to].size() };
	G[from].push_back(e1);
	edge e2 = { from, 0, G[from].size() - 1 };
	G[to].push_back(e2);

}

// �����p�X��DFS�ŒT��
int dfs(int v, int t, int f) {
	if (v == t) {
		return f;
	}

	used[v] = true;

	for (int i = 0; i < G[v].size(); i++) {
		edge& e = G[v][i];
		if (!used[e.to] && e.cap > 0) {
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

// s����t�ւ̍ő嗬�����߂�
int max_flow(int s, int t) {
	int flow = 0;
	while (true) {
		memset(used, 0, sizeof(used));
		int f = dfs(s, t, INF);
		if (f == 0) {
			return flow;
		}
		flow += f;
	}
}

int main() {
	
	cin >> V >> E;

	for (int i = 0; i < E; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		add_edge(u, v, c);
	}


	cout << max_flow(0, V - 1) << endl;

	return 0;
}