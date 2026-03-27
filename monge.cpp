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
#include <random>
#include <chrono>
using namespace std;
const long long LINF = 3e18 + 7;
const int MAX_N = 5000010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
const int INF = 2147483647;
//using ll = long long;

// 問題
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2415

// 参考
// https://omochan.hatenablog.com/entry/2017/07/08/122642
// https://blog.hamayanhamayan.com/entry/2017/03/20/234711

int N;
long long w[MAX_N];
long long cum[MAX_N];
long long dp[4040][4040];
int A[4010][4010];

int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> w[i];
	}
	for (int i = 0; i < N; i++) {
		cum[i + 1] = cum[i] + w[i];
	}
	for (int i = 0; i < N; i++) {
		A[i][i] = i;
	}

	for (int w = 1; w < N; w++) {
		for (int l = 0; l + w <= N; l++) {
			int r = l + w;
			int a = A[l][r - 1];
			int b = A[l + 1][r];
			long long m = LINF;
			int at = -1;
			for (int i = a; i <= b; i++) {
				if (l > i || i >= r) continue;
				long long tm = dp[l][i] + dp[i + 1][r];
				if (tm <= m) {
					at = i;
					m = tm;
				}
			}
			dp[l][r] = m + cum[r + 1] - cum[l];
			A[l][r] = at;
		}
	}

	cout << dp[0][N - 1] << endl;

	return 0;
}