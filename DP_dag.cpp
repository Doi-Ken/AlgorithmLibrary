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
const int INF = 1000000007;
const long long LINF = 3e18 + 7;
const int MAX_N = 1200010;
const int MAX_W = 600010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long; 

int H, W;
int a[1010][1010];

vector<int> G[1010000];
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { -1, 0, 1, 0 };
int deg[1010000];
long long dp[1010000];
long long mod = 1000000007;

int main() {

	cin >> H >> W;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> a[i][j];
		}
	}

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			
			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				if (nx >= 0 && nx < W && ny >= 0 && ny < H && a[y][x] < a[ny][nx]) {
					G[y * W + x].push_back(ny * W + nx);
					deg[ny * W + nx]++;
				}
			}
		}
	}

	queue<int> que;

	for (int i = 0; i < H * W; i++) {
		if (deg[i] == 0) {
			que.push(i);
			dp[i] = 0LL;
		}
	}

	while (!que.empty()) {
		int v = que.front();
		que.pop();
		for (int i = 0; i < G[v].size(); i++) {
			int u = G[v][i];

			dp[u] += (dp[v] + 1LL);
			dp[u] %= mod;
			deg[u]--;
			if (deg[u] == 0) {
				que.push(u);
			}
		}
	}
	long long ans = H * W;
	for (int i = 0; i < H * W; i++) {
		ans += dp[i];
		ans %= mod;
	}

	cout << ans << endl;
	


	return 0;
}