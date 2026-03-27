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

// 分割数
// 例題: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_L
// 説明: https://algo-logic.info/partition_with_k/
// 蟻本 p. 66
// 参考: https://incognita.hatenablog.com/entry/20110305/1299344781

long long mod = 1000000007;

int N, K;
long long p[1010][1010]; // 自然数nをk個の1以上の整数に分割する方法：区別できない n 個の要素を区別できない k 個ちょうどのブロックに分割する方法の数
long long dp[1010][1010]; // 自然数nをk個の0以上の整数に分割する方法：区別できない n 個の要素を区別できない高々 k 個のブロックに分割する方法の数 (蟻本)

void solve_p() {
	p[0][0] = 1;
	for (int n = 1; n <= 1000; n++) {
		for (int k = 1; k <= 1000; k++) {
			if (n - k >= 0) {
				p[n][k] = (p[n - 1][k - 1] + p[n - k][k]) % mod;
			}
			else {
				p[n][k] = p[n - 1][k - 1];
			}
		}
	}
}

void solve_dp() {
	dp[0][0] = 1;
	for (int i = 1; i <= 1000; i++) {
		for (int j = 0; j <= 1000; j++) {
			if (j - i >= 0) {
				dp[j][i] = (dp[j][i - 1] + dp[j - i][i]) % mod;
			}
			else {
				dp[j][i] = dp[j][i - 1];
			}
		}
	}
}

int main() {
	

	cin >> N >> K;

	solve_p();
	solve_dp();

	
	cout << dp[N][K] << endl;

	int cum = 0;
	for (int i = 1; i <= K; i++) {
		cum += p[N][i];
		cum %= mod;
	}
	cout << cum << endl;
	cout << p[N][K] << endl;

	
	return 0;
}