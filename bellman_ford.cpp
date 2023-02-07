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
const int INF = 10000000000;
const long long LINF = 3e17 + 7;
const int MAX_N = 700010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;


// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja
int V;
int E;
int r;
struct edge { int from, to; long long d; };
edge edges[MAX_N];
typedef pair<long long, int> P;
long long dist[MAX_N];

bool bellman_ford(int s) {
	for (int i = 0; i < V; i++) {
		dist[i] = LINF;
	}

	dist[s] = 0;
	for (int i = 0; i < 2 * V; i++) {
		for (int j = 0; j < E; j++) {
			edge e = edges[j];
			if (dist[e.from] != LINF && dist[e.to] > dist[e.from] + e.d) {
				dist[e.to] = dist[e.from] + e.d;
				// あくまで終点が無限に最適になり得る負の閉路が検出された場合 trueとなる
				// もし終点に関係ないようなどの負の閉路も認めない場合、e.to == V - 1を削除すれば良い。
				// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja　では、e.to=V-1は削除（どの負閉路も認めない）
				if (i >= V - 1 && e.to == V - 1) return true;
			}
		}
	}
	return false;
}

int main() {

	cin >> V >> E >> r;

	for (int i = 0; i < E; i++) {
		int s, t;
		long long d;
		cin >> s >> t >> d;
		edge e;
		e.from = s;
		e.to = t;
		e.d = d;
		edges[i] = e;
	}

	if (bellman_ford(r)) {
		cout << "NEGATIVE CYCLE" << endl;
	}
	else {
		for (int i = 0; i < V; i++) {
			if (dist[i] >= 10000000000) {
				cout << "INF" << endl;
			}
			else {
				cout << dist[i] << endl;
			}
		}
	}



	return 0;
}