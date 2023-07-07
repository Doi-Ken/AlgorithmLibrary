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
const int MAX_N = 200010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// RMQ and RAQ (遅延評価セグメント木) Starry Sky Tree
// AOJ DSL_2_H https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H&lang=jp
// https://qiita.com/ageprocpp/items/9ea58ac181d31cfdfe02
// https://algo-logic.info/segment-tree/

int N;
long long dat[2 * MAX_N - 1];
long long lazy[2 * MAX_N - 1];

// initialization
void init(int n_) {
	N = 1;
	while (N < n_) N *= 2;

	for (int i = 0; i < 2 * N - 1; i++) {
		dat[i] = LINF;
		lazy[i] = LINF;
	}
}

void eval(int k) {
	if (lazy[k] == LINF) {
		return;
	}
	if (k < N - 1) {
		lazy[k * 2 + 1] = (lazy[k * 2 + 1] == LINF) ? lazy[k] : lazy[k * 2 + 1] + lazy[k];
		lazy[k * 2 + 2] = (lazy[k * 2 + 2] == LINF) ? lazy[k] : lazy[k * 2 + 2] + lazy[k];
	}
	dat[k] = (dat[k] == LINF) ? lazy[k] : dat[k] + lazy[k];
	lazy[k] = LINF;
}


void update(int a, int b, long long x, int k, int l, int r) {

	eval(k);
	if (a <= l && r <= b) {  // 完全に内側の時
		lazy[k] = (lazy[k] == LINF) ? x : lazy[k] + x;
		eval(k);
	}
	else if (a < r && l < b) {                     // 一部区間が被る時
		update(a, b, x, k * 2 + 1, l, (l + r) / 2);  // 左の子
		update(a, b, x, k * 2 + 2, (l + r) / 2, r);  // 右の子
		dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
	}
}

// [a, b) の最小値を求める
// k は節点の番号、l, rはその節点が[l, r)に対応づいていることを表す。
// したがって、外からquery(a, b, 0, 0, n)をよぶ。
// (k(0)番目の節点、l(0) ～ r(n)の間を初めは指定)
long long query(int a, int b, int k, int l, int r) {
	eval(k);
	// [a, b)と[l, r)が交差しなければ INF
	if (r <= a || b <= l) {
		return LINF;
	}

	// [a, b) が[l, r)を完全に含んでいれば、この節点の値
	if (a <= l && r <= b) {
		return dat[k];
	}
	else {
		long long v1 = query(a, b, k * 2 + 1, l, (l + r) / 2);
		long long v2 = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return min(v1, v2);
	}
}

int Q;
long long L[MAX_N], R[MAX_N];
long long X[MAX_N];
int T[MAX_N];
long long A[MAX_N];

int main() {

	cin >> N >> Q;

	for (int q = 0; q < Q; q++) {
		cin >> T[q];
		if (T[q] == 1) {
			cin >> L[q] >> R[q];
		}
		else {
			cin >> L[q] >> R[q] >> X[q];
		}
	}

	init(N);
	for (int i = 0; i < 2 * N - 1; i++) {
		dat[i] = 0;
	}

	for (int q = 0; q < Q; q++) {
		if (T[q] == 1) {
			cout << query(L[q], R[q] + 1, 0, 0, N + 1) << endl;
		}
		else {
			update(L[q], R[q] + 1, X[q], 0, 0, N + 1);
		}
	}


	return 0;
}