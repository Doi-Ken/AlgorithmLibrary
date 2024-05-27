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
const int MAX_N = 5000010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// https://atcoder.jp/contests/dp/tasks/dp_g

int dp[MAX_N];
int N, M;
int x[MAX_N], y[MAX_N];
vector<int> G[MAX_N];

int dfs(int v) {

	if (dp[v] >= 0) {
		return dp[v];
	}

	if (G[v].size() == 0) {
		return dp[v] = 0;
	}

	for (int i = 0; i < G[v].size(); i++) {
		int u = G[v][i];
		dp[v] = max(dp[v], dfs(u) + 1);
	}

	return dp[v];
}

int main() {

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> x[i] >> y[i];
		x[i]--;
		y[i]--;
		G[y[i]].push_back(x[i]);
	}

	for (int i = 0; i <= N; i++) {
		dp[i] = -1;
	}

	int ans = 0;
	for (int i = 0; i < N; i++) {
		ans = max(ans, dfs(i));
	}

	cout << ans << endl;


	return 0;
}