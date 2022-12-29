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

int N;
long long A[20][20];
long long cost[MAX_N][20];

bool has_bit(int n, int i) {
	return (n & (1 << i)) > 0;
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
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
						cost[n | (1 << j)][j] = min(cost[n | (1 << j)][j], cost[n][i] + A[i][j]);
						// cout << bitset<5>(n | (1 << j)) << ", " << i << ", " << j << " =  " << cost[n | (1 << j)][j] << endl;
					}
				}
			}
		}
	}

	cout << cost[ALL - 1][0] << endl;

	return 0;
}