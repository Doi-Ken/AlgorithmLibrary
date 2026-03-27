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

// p. 155 segment tree
// AOJ DSL_2_A https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A

int N;
long long dat[2 * MAX_N - 1];

// initialization
void init(int n_) {
	N = 1;
	while (N < n_) N *= 2;

	for (int i = 0; i < 2 * N - 1; i++) {
		dat[i] = LINF;
	}
}

// k番目の値 (0-indexed) をaに変更
void update(int k, long long a) {
	
	// 葉の節点 (一番最下層のノードは N - 1 + k 番目で保持している。(１番下の層以外が N - 1個))
	k += N - 1;
	dat[k] = a;

	while (k > 0) {
		k = (k - 1) / 2;
		dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
	}
}

// [a, b) の最小値を求める
// k は節点の番号、l, rはその節点が[l, r)に対応づいていることを表す。
// したがって、外からquery(a, b, 0, 0, n)をよぶ。
// (k(0)番目の節点、l(0) ～ r(n)の間を初めは指定)
long long query(int a, int b, int k, int l, int r) {

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

int main() {

	cin >> N >> Q;
	init(N);

	for (int q = 0; q < Q; q++) {
		int com;
		
		cin >> com;
		if (com == 0) {
			int x;
			long long y;

			cin >> x >> y;
			update(x, y);
		}
		else {
			int x, y;
			cin >> x >> y;
			cout << query(x, y + 1, 0, 0, N) << endl;
		}


	}


	return 0;
}