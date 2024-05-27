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
#include <chrono>
#include <random>
using namespace std;
const int INF = 100000000;
const long long LINF = 1e18 + 7;
const int MAX_N = 5000010;
const int MAX_W = 1102;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
using ll = long long;

// https://atcoder.jp/contests/abc291/tasks/abc291_e

int N, M;
vector<int> G[MAX_N];
int X[MAX_N], Y[MAX_N];
int deg[MAX_N];


int main() {

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> X[i] >> Y[i];
		X[i]--;
		Y[i]--;
		G[X[i]].push_back(Y[i]);
		deg[Y[i]]++;
	}

	vector<int> ans(N);
	queue<int> q;

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (deg[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		if (q.size() != 1) {
			cout << "No" << endl;
			return 0;
		}
		int v = q.front();
		q.pop();
		cnt++;
		ans[v] = cnt;
		for (int i = 0; i < G[v].size(); i++) {
			int u = G[v][i];
			deg[u]--;
			if (deg[u] == 0) {
				q.push(u);
			}
		}
	}

	cout << "Yes" << endl;
	for (int i = 0; i < N; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;



	return 0;
}
