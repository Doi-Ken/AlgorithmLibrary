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
const int MAX_N = 10010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

long long cost[MAX_N][MAX_N]; // cost[u][v]はe=(u,v)のコスト（存在しない場合はINF, ただし、cost[i][i] = 0）
int V, E;

void warshall_floyd() {

	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
			}
		}
	}
}


int main() {

	cin >> V >> E;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cost[i][j] = LINF;
		}
		cost[i][i] = 0;
	}

	for (int i = 0; i < E; i++) {
		int u, v;
		long long c;
		cin >> u >> v >> c;
		cost[u][v] = c;
	}

	warshall_floyd();

	// 対角が負になる場合は負の閉路を持つ
	for (int i = 0; i < V; i++) {
		if (cost[i][i] < 0) {
			cout << "NEGATIVE CYCLE" << endl;
			return 0;
		}
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (cost[i][j] >= 3e16) {
				cout << "INF";
			}
			else {
				cout << cost[i][j];
			}
			if (j != V - 1) {
				cout << " ";
			}
		}
		cout << endl;
	}

	return 0;
}