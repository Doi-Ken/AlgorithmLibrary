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
const int MAX_N = 600010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// https://qiita.com/drken/items/ecd1a472d3a0e7db8dce
long long N, W;
long long v[MAX_N], w[MAX_N];
long long dpw[210][210 * 1010];
long long dpv[210][210 * 1010];

map<long long, long long> dpN[MAX_N];

bool flag_N;
bool flag_w;
bool flag_v;


long long rec(long long i, long long j) {
	if (dpN[i][j] > 0) {
		return dpN[i][j];
	}
	long long res;
	if (i == N) {
		res = 0L;
	}
	else if (j < w[i]) {
		res = rec(i + 1, j);
	}
	else {
		res = max(rec(i + 1, j), rec(i + 1, j - w[i]) + v[i]);
	}

	return dpN[i][j] = res;
}


int main() {

	cin >> N >> W;

	flag_N = true;
	flag_w = true;
	flag_v = true;
	if (N > 30) {
		flag_N = false;
	}
	for (long long i = 0; i < N; i++) {
		cin >> v[i] >> w[i];
		if (v[i] > 1000L) {
			flag_v = false;
		}
		if (w[i] > 1000L) {
			flag_w = false;
		}
	}

	if (flag_w) {
		dpw[0][0] = 0L;

		for (long long i = 0; i < N; i++) {
			for (long long j = 0; j <= W; j++) {
				dpw[i + 1][j] = dpw[i][j];
				if (j >= w[i]) {
					dpw[i + 1][j] = max(dpw[i + 1][j], dpw[i][j - w[i]] + v[i]);
				}
			}
		}
		cout << dpw[N][W] << endl;
	}
	else if (flag_v) {
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N * 1001; j++) {
				dpv[i][j] = LINF;
			}
		}
		dpv[0][0] = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= N * 1001; j++) {
				if (j < v[i]) {
					dpv[i + 1][j] = dpv[i][j];
				}
				else {
					dpv[i + 1][j] = min(dpv[i][j], dpv[i][j - v[i]] + w[i]);
				}
			}
		}
		long long res = 0;
		for (int i = 0; i <= N * 1001; i++) {
			if (dpv[N][i] <= W) {
				res = i;
			}
		}
		cout << res << endl;
	}
	else {

		cout << rec(0, W) << endl;

	}


	return 0;
}