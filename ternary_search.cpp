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
const int MAX_N = 300010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;


// ternary_search
// https://atcoder.jp/contests/typical90/tasks/typical90_br
// éQçl: https://qiita.com/DaikiSuyama/items/84df26daad11cf7da453
long long X[MAX_N], Y[MAX_N];
long long gx, gy;
int N;

long long funcX(long long x) {
	long long ans = 0;
	for (int i = 0; i < N; i++) {
		ans += abs(X[i] - x);
	}

	return ans;
}

long long funcY(long long x) {
	long long ans = 0;
	for (int i = 0; i < N; i++) {
		ans += abs(Y[i] - x);
	}

	return ans;
}

long long ternary_searchX(long long l, long long r) {
	long long lb = l - 1;
	long long ub = r;

	while (ub - lb > 2) {
		int mid_l = lb + (ub - lb) / 3;
		int mid_r = ub - (ub - lb) / 3;
		if (funcX(mid_l) < funcX(mid_r)) {
			ub = mid_r;
		}
		else {
			lb = mid_l;
		}
	}

	return ub;
}

long long ternary_searchY(long long l, long long r) {
	long long lb = l - 1;
	long long ub = r;

	while (ub - lb > 2) {
		int mid_l = lb + (ub - lb) / 3;
		int mid_r = ub - (ub - lb) / 3;
		if (funcY(mid_l) < funcY(mid_r)) {
			ub = mid_r;
		}
		else {
			lb = mid_l;
		}
	}

	return ub;
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> X[i] >> Y[i];
	}

	for (int i = 0; i < N; i++) {
		gx += X[i];
		gy += Y[i];
	}

	sort(X, X + N);
	sort(Y, Y + N);

	long long canx = ternary_searchX(X[0], X[N - 1]);
	long long cany = ternary_searchY(Y[0], Y[N - 1]);
	
	long long ansx = 0;
	for (int i = 0; i < N; i++) {
		ansx += abs(X[i] - canx);
	}

	long long ansy= 0;
	for (int i = 0; i < N; i++) {
		ansy += abs(Y[i] - cany);
	}

	canx = canx - 1;
	cany = cany - 1;

	long long ansx_ = 0;
	for (int i = 0; i < N; i++) {
		ansx_ += abs(X[i] - canx);
	}

	long long ansy_ = 0;
	for (int i = 0; i < N; i++) {
		ansy_ += abs(Y[i] - cany);
	}

	ansx = min(ansx, ansx_);
	ansy = min(ansy, ansy_);

	cout << ansx + ansy << endl;


	return 0;
}