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
const int MAX_N = 2000010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// 蟻本 p. 244
// intersection_of_two_circles
// 2円の交点（サンプル）
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000432cc7/0000000000432ad3

typedef long long ll;
int N;
double X[MAX_N], Y[MAX_N], R[MAX_N];

// 中心(x, y)半径r の円が囲む集合を求める
ll cover(double x, double y, double r) {
	ll S = 0;
	for (int i = 0; i < N; i++) {
		if (R[i] <= r) {
			double dx = x - X[i], dy = y - Y[i], dr = r - R[i];
			if (dx * dx + dy * dy <= dr * dr) {
				S |= 1LL << i;
			}
		}
	}
	return S;
}


// 半径rの円2つですべてを囲うことが可能かを判定
bool C(double r) {
	vector<ll> cand; // 1つの縁で囲える集合のリスト
	cand.push_back(0);

	// パターンA
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (R[i] < r && R[j] < r) {
				// 二円の交点を計算
				double X1 = X[i], Y1 = Y[i], r1 = r - R[i];
				double X2 = X[j], Y2 = Y[j], r2 = r - R[j];
				double dx = X2 - X1, dy = Y2 - Y1;
				double a = dx * dx + dy * dy;
				double b = ((r1 * r1 - r2 * r2) / a + 1.0) / 2.0;
				double d = r1 * r1 / a - b * b;

				if (d >= 0) {
					d = sqrt(d);
					double x3 = X1 + dx * b;
					double y3 = Y1 + dy * b;
					double x4 = -dy * d;
					double y4 = dx * d;
					// 誤差を考慮し、iとjは特別扱いする
					ll ij = (1LL << i) | (1LL << j);
					cand.push_back(cover(x3 - x4, y3 - y4, r) | ij);
					cand.push_back(cover(x3 + x4, y3 + y4, r) | ij);
				}
				
			}

		}
	}

	// パターンB
	for (int i = 0; i < N; i++) {
		if (R[i] <= r) {
			cand.push_back(cover(X[i], Y[i], r) | (1LL << i));
		}
	}
	
	// 円の候補から2つ取り出して全てを囲えているかを調べる
	for (int i = 0; i < cand.size(); i++) {
		for (int j = 0; j < i; j++) {
			if ((cand[i] | cand[j]) == (1LL << N) - 1) {
				return true;
			}
		}
	}
	return false;
}


void solve(int n) {
	// 半径rを二分探索
	double lb = 0, ub = 10000;
	for (int i = 0; i < 100; i++) {
		double mid = (lb + ub) / 2;
	
		if (C(mid)) {
			ub = mid;
		}
		else {
			lb = mid;
		}
	}


	cout << "Case #" << n << ": ";
	cout << fixed << setprecision(6) << ub << endl;
}


int main() {

	
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {

		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> X[i] >> Y[i] >> R[i];
		}

		solve(t + 1);
	}


	return 0;
}