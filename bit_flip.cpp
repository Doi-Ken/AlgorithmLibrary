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
const int MAX_N = 10000010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// poj3276
// 蟻本 p.139

int N;
int dir[MAX_N];
int f[MAX_N];

int calc(int K) {
	memset(f, 0, sizeof(f));
	int res = 0;
	int sum = 0;
	for (int i = 0; i + K <= N; i++) {
		if ((dir[i] + sum) % 2 != 0) {
			res++;
			f[i] = 1;
		}

		sum += f[i];
		if (i - K + 1 >= 0) {
			sum -= f[i - K + 1];
		}
	}

	for (int i = N - K + 1; i < N; i++) {
		if ((dir[i] + sum) % 2 != 0) {
			return -1;
		}
		if (i - K + 1 >= 0) {
			sum -= f[i - K + 1];
		}
	}
	return res;
}

void solve() {
	int K = 1, M = N;
	for (int k = 1; k <= N; k++) {
		int m = calc(k);
		if (m >= 0 && M > m) {
			M = m;
			K = k;
		}
	}

	cout << K << " " << M << endl;
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		char c[2];
		scanf("%1s", c);
		if (c[0] == 'F') {
			dir[i] = 0;
		}
		else {
			dir[i] = 1;
		}
	}

	solve();


	return 0;
}