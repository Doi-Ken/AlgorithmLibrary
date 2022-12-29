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
const int MAX_N = 6000100;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

vector<int> G[MAX_N];
int V;
int color[MAX_N];

// bipartite graph (2•”ƒOƒ‰ƒt”»’è)
// ‹a–{ p. 93
// 4 4
// 0 1
// 1 2
// 2 3
// 0 3

bool dfs(int v, int c) {
	color[v] = c;
	for (int i = 0; i < G[v].size(); i++) {
		if (color[G[v][i]] == c) {
			return false;
		}
		if (color[G[v][i]] == 0 && !dfs(G[v][i], -c)) {
			return false;
		}
	}
	return true;
}

int main() {

	int E;
	cin >> V >> E;
	for (int i = 0; i < E; i++) {
		int f, t;
		cin >> f >> t;
		G[f].push_back(t);
		G[t].push_back(f);
	}

	for (int i = 0; i < V; i++) {
		if (color[i] == 0) {
			if (!dfs(i, 1)) {
				cout << "No" << endl;
				return 0;
			}
		}
	}

	cout << "Yes" << endl;

	return 0;
}