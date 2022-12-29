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
const int MAX_N = 10010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

int N;
int w[MAX_N], v[MAX_N];
int W;
int dp[MAX_N][MAX_N];

// 3
// 3 4
// 4 5
// 2 3
// 7

int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> w[i] >> v[i];
	}
	cin >> W;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= W; j++) {
			if (j < w[i]) {
				dp[i + 1][j] = dp[i][j];
			}
			else {
				dp[i + 1][j] = max(dp[i][j], dp[i + 1][j - w[i]] + v[i]);
			}

		}
	}

	cout << dp[N][W] << endl;
	
	return 0;
}