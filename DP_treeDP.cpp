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
//using ll = long long

// tree DP
// https://atcoder.jp/contests/dp/tasks/dp_p
// https://blog.hamayanhamayan.com/entry/2019/01/11/002932


int N;
vector<int> G[100010];
long long dp[100010][2];
long long mod = 1000000007;


void dfs(int v, int fr = -1) {
	dp[v][0] = dp[v][1] = 1;
	for (int i = 0; i < G[v].size(); i++) {
		int to = G[v][i];
		if (to != fr) {
			dfs(to, v);
			dp[v][0] = (dp[v][0] * (dp[to][0] + dp[to][1])) % mod;
			dp[v][1] = (dp[v][1] * dp[to][0]) % mod;
		}
	}

}

int main() {

	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		G[a].push_back(b);
		G[b].push_back(a);

	}

	dfs(0);

	long long ans = (dp[0][0] + dp[0][1]) % mod;

	cout << ans << endl;


	return 0;
}