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
const int MAX_N = 6010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;


// prim
long long cost[MAX_N][MAX_N];
long long mincost[MAX_N];
bool used[MAX_N];
long long V, E;

long long prim() {
	for (long long i = 0; i < V; i++) {
		mincost[i] = INF;
		used[i] = false;
	}

	mincost[0] = 0;
	long long res = 0;

	while (true) {
		long long v = -1;

		for (long long u = 0; u < V; u++) {
			if (!used[u] && (v == -1 || mincost[u] < mincost[v])) {
				v = u;
			}
		}

		if (v == -1) {
			break;
		}
		used[v] = true;
		res += mincost[v];

		for (int u = 0; u < V; u++) {
			mincost[u] = min(mincost[u], cost[v][u]);
		}
	}
	return res;
}

int main() {

	cin >> V >> E;
	for (long long v = 0; v < V; v++) {
		for (long long u = 0; u < V; u++) {
			cost[v][u] = INF;
		}
		cost[v][v] = 0;
	}
	for (long long e = 0; e < E; e++) {
		long long v, u, d;
		cin >> v >> u >> d;
		cost[v][u] = d;
		cost[u][v] = d;
	}

	cout << prim() << endl;

	return 0;
}