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

// p. 163 segment_tree Sum
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E 
// AOJ RAQ base
// POJ 3468

long long N;
long long dat[2 * MAX_N - 1];
long long datb[2 * MAX_N - 1];

// [a, b) にxを加算する
// k は節点の番号、l, rはその節点が[l, r)に対応づいていることを表す。
void add(long long a, long long b, long long x, long long k, long long l, long long r) {


	if (a <= l && r <= b) {
		dat[k] += x;
	}
	else if (l < b && a < r) {
		datb[k] += (min(b, r) - max(a, l)) * x;
		add(a, b, x, k * 2 + 1, l, (l + r) / 2);
		add(a, b, x, k * 2 + 2, (l + r) / 2, r);
	}
}

// [a, b) の和を計算する
// k は節点の番号、l, rはその節点が[l, r)に対応づいていることを表す。
long long sum(long long a, long long b, long long k, long long l, long long r) {

	// [a, b)と[l, r)が交差しなければ0
	if (r <= a || b <= l) {
		return 0;
	}

	// [a, b) が[l, r)を完全に含んでいれば、この節点の値
	if (a <= l && r <= b) {
		return dat[k] * (r - l) + datb[k];
	}
	else {
		long long res = (min(b, r) - max(a, l)) * dat[k];
		res += sum(a, b, k * 2 + 1, l, (l + r) / 2);
		res += sum(a, b, k * 2 + 2, (l + r) / 2, r);
		return res;
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
			cin >> L[q];
		}
		else {
			cin >> L[q] >> R[q] >> X[q];
		}
	}

	for (int q = 0; q < Q; q++) {
		if (T[q] == 1) {
			cout << sum(L[q], L[q] + 1, 0, 0, N + 1) << endl;
		}
		else {
			add(L[q], R[q] + 1, X[q], 0, 0, N + 1);
		}
	}


	return 0;
}