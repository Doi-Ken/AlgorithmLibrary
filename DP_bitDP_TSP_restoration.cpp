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

// bitDP_TSP_restoration
// https://atcoder.jp/contests/s8pc-1/tasks/s8pc_1_g

int N, M;
long long A[20][20];
long long T[20][20];
long long cost[1 << 20][20];

bool has_bit(int n, int i) {
	return (n & (1 << i)) > 0;
}

int ans = 0;

void dfs(int n, int to) {

	if (n == 0) {
		ans++;
		return;
	}


	for (int i = 0; i < N; i++) {
		if (has_bit(n, i) || ((n & ~(1 << to)) == 0) && i == 0) {

			//			cout << "[" << n << "][" << to << "] from " << "[" << (n & ~(1 << to)) << "][" << i << "] " << endl;
			if (cost[n & ~(1 << to)][i] + A[i][to] == cost[n][to] && cost[n][to] <= T[i][to]) {
				//cout << "[" << n << "][" << to << "] from " << "[" << (n & ~(1 << to)) << "][" << i << "] " << endl << endl;
				dfs(n & ~(1 << to), i);
			}
		}
	}
}

int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A[i][j] = LINF;
			T[i][j] = LINF;
		}
	}

	for (int i = 0; i < M; i++) {
		int s, t;
		long long d, time;
		cin >> s >> t >> d >> time;
		s--;
		t--;
		A[s][t] = A[t][s] = d;
		T[s][t] = T[t][s] = time;
	}


	int ALL = 1 << N;

	for (int n = 0; n < ALL; n++) {
		for (int i = 0; i < N; i++) {
			cost[n][i] = LINF;
		}
	}
	cost[0][0] = 0;

	for (int n = 0; n < ALL; n++) {
		// cout << bitset<5>(n) << endl;
		for (int i = 0; i < N; i++) {

			if (has_bit(n, i) || n == 0) { //’Tõ‡˜“I‚É‚È‚­‚Ä‚à—Ç‚¢‚ª‚ ‚Á‚½•û‚ªˆÓ–¡‚ª’¼Š´“I
				for (int j = 0; j < N; j++) {
					if (has_bit(n, j) || i == j) {
						continue;
					}
					else {
						long long local = min(cost[n | (1 << j)][j], cost[n][i] + A[i][j]);
						if (local <= T[i][j]) {
							cost[n | (1 << j)][j] = local;
						}
					}
				}
			}
		}
	}

	//for (int i = 0; i < ALL; i++) {
	//	for (int j = 0; j < N; j++) {
	//		cout << cost[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	if (cost[ALL - 1][0] == LINF) {
		cout << "IMPOSSIBLE" << endl;
	}
	else {
		dfs(ALL - 1, 0);
		cout << cost[ALL - 1][0] << " " << ans << endl;
	}


	return 0;
}