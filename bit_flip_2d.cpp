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

const int dx[5] = { -1, 0, 0, 0, 1 };
const int dy[5] = { 0, -1, 0, 1, 0 };

int M, N;
int tile[20][20];

int opt[20][20];
int flip[20][20];

int get(int x, int y) {
	int c = tile[x][y];
	for (int d = 0; d < 5; d++) {
		int x2 = x + dx[d], y2 = y + dy[d];
		if (0 <= x2 && x2 < M && 0 <= y2 && y2 < N) {
			c += flip[x2][y2];
		}
	}

	return c % 2;
}

int calc() {
	for (int i = 1; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (get(i - 1, j) != 0) {
				flip[i][j] = 1;

			}
		}
	}
	for (int j = 0; j < N; j++) {
		if (get(M - 1, j) != 0) {
			return -1;
		}
	}

	int res = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			res += flip[i][j];
		}
	}
	return res;
}

bool has_bit(int n, int i) {
	return ((n & (1 << i)) > 0);
}


void solve() {
	int res = -1;

	for (int n = 0; n < (1 << N); n++) {
		memset(flip, 0, sizeof(flip));
		for (int j = 0; j < N; j++) {
			if (has_bit(n, j)) {
				flip[0][j] = 1;
			}
			else {
				flip[0][j] = 0;
			}
		}
		int num = calc();
		if (num >= 0 && (res < 0 || res > num)) {
			res = num;
			memcpy(opt, flip, sizeof(flip));
		}
	}

	if (res < 0) {
		cout << "IMPOSSIBLE" << endl;
	}
	else {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cout << opt[i][j] << " ";
			}
			cout << endl;
		}
	}
}

int main() {

	cin >> M >> N;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> tile[i][j];
		}
	}

	solve();

	return 0;
}