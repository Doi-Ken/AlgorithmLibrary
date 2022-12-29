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
const int MAX_N = 20010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// ‚¾‚é‚Ü—Ž‚Æ‚µ
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1611&lang=jp

int N;
int w[MAX_N];
int dp[MAX_N][MAX_N];

int main() {
	
	while (true) {
		cin >> N;
		if (N == 0) {
			break;
		}
		for (int i = 0; i < N; i++) {
			cin >> w[i];
		}

		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++) {
				dp[i][j] = 0;
			}
		}

		for (int W = 2; W <= N; W++) {
			for (int l = 0; l < N; l++) {
				int r = l + W;
				if (r > N) {
					continue;
				}

				if (dp[l + 1][r - 1] == W - 2 && abs(w[l] - w[r - 1]) <= 1) {
					dp[l][r] = W;
				}

				for (int mid = l; mid <= r; mid++) {
					dp[l][r] = max(dp[l][r], dp[l][mid] + dp[mid][r]);
				}
			}
		}

		cout << dp[0][N] << endl;

	}

	return 0;
}