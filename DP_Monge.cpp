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

// https://atcoder.jp/contests/atc002/tasks/atc002_c
// n <= 3000 Monge

int N;
long long w[MAX_N];
long long dp[3010][3010];
long long cum[3010];
int A[3010][3010];

int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> w[i];
		cum[i + 1] = cum[i] + w[i];
	}

	for (int i = 0; i < N; i++) {
		A[i][i] = i;
	}

	for (int k = 1; k < N; k++) {
		for (int i = 0; i <= N - k; i++) {
			int j = i + k;
			int a = A[i][j - 1];
			int b = A[i + 1][j];
			long long m = LINF;
			int at = -1;
			for (int l = a; l <= b; l++) {
				if (i > l || l >= j) continue;
				long long tm = dp[i][l] + dp[l + 1][j];
				
				if (tm <= m) {
					at = l;
					m = tm;
				}
			}

			dp[i][j] = m + cum[j + 1] - cum[i];
			A[i][j] = at;
		}

	}

	cout << dp[0][N - 1]  << endl;


	return 0;
}