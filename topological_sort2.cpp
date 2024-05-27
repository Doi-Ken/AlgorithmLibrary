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
const int MAX_N = 5000010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// https://atcoder.jp/contests/abc223/tasks/abc223_d

vector<int> G[MAX_N];
int par[MAX_N];
int N, M;
vector<int> ans;
int deg[MAX_N];
set<int> m[MAX_N];
bool visited[MAX_N];


int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		par[i] = -1;
	}
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		if (m[a].find(b) != m[a].end()) {
			continue;
		}
		m[a].insert(b);
		G[a].push_back(b);
		deg[b]++;
	}

	vector<int> ans;
	priority_queue<int, vector<int>, greater<int>> q;

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (deg[i] == 0) {
			q.push(i);
		}
	}

	if (q.empty()) {
		cout << -1 << endl;
		return 0;
	}

	while (!q.empty()) {
		int v = q.top();
		q.pop();
		ans.push_back(v);
		for (int i = 0; i < G[v].size(); i++) {
			int u = G[v][i];
			deg[u]--;
			if (deg[u] == 0) {
				q.push(u);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (deg[i] != 0) {
			cout << -1 << endl;
			return 0;
		}
	}

	for (int i = 0; i < ans.size(); i++) {
		visited[ans[i]] = true;
	}

	
	int j = 0;
	for (int i = 0; i < ans.size(); i++) {
		int c = ans[i];
		for (; j < c && j < N; j++) {
			if (!visited[j]) {
				cout << j + 1 << " ";
			}
		}
		cout << c + 1 << " ";
	}

	for (; j < N; j++) {
		if (!visited[j]) {
			cout << j + 1 << " ";
		}
	}

	cout << endl;

	
	return 0;
}