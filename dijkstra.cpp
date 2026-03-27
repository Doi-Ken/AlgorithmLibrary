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
const long long LINF = 3e18 + 7;
const int MAX_N = 700010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

int V;
int E;
int r;
struct edge { int to; long long d; };
vector<edge> edges[MAX_N];
typedef pair<long long, int> P;
long long dist[MAX_N];

void dijkstra(int s) {

	for (int i = 0; i < V; i++) {
		dist[i] = LINF;
	}

	priority_queue<P, vector<P>, greater<P> > que;
	
	dist[s] = 0;
	que.push(P(0, s));

	while (!que.empty()) {
		int u = que.top().second;
		long long d = que.top().first;
		que.pop();
		
		if (dist[u] < d) {
			continue;
		}

		for (int i = 0; i < edges[u].size(); i++) {
			int v = edges[u][i].to;
			long long uvd = edges[u][i].d;
			if (d + uvd < dist[v]) {
				dist[v] = d + uvd;
				que.push(P(dist[v], v));
			}

		}
	}

}


int main() {

	cin >> V >> E >> r;

	for (int i = 0; i < E; i++) {
		int s, t;
		long long d;
		cin >> s >> t >> d;
		edge e;
		e.to = t;
		e.d = d;
		edges[s].push_back(e);
		e.to = s;
		edges[t].push_back(e);
	}

	dijkstra(r);

	for (int i = 0; i < V; i++) {
		if (dist[i] == LINF) {
			cout << "INF" << endl;
		}
		else {
			cout << dist[i] << endl;
		}
	}


	return 0;
}