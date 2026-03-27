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

// 蟻本 p. 233
// POJ 2187
// http://poj.org/problem?id=2187

// 8
// 0 5
// 1 8
// 3 4
// 5 0
// 6 2
// 6 6
// 8 3
// 8 7


double EPS = 1e-10;

// 誤差を考慮して足し算を行う
double add(double a, double b) {
	if (abs(a + b) < EPS * (abs(a) + abs(b))) {
		return 0;
	}
	return a + b;
}

// 2次元ベクトル構造体
struct P {
	double x, y;
	P() {};
	P(double x, double y) : x(x), y(y) {
	}
	P operator + (P p) {
		return P(add(x, p.x), add(y, p.y));
	}
	P operator - (P p) {
		return P(add(x, -p.x), add(y, -p.y));
	}
	P operator * (double d) {
		return P(x * d, y * d);
	}
	double dot(P p) {
		return add(x * p.x, y * p.y);
	}
	double det(P p) {
		return add(x * p.y, -y * p.x);
	}
};

bool cmp_x(const P& p, const P& q) {
	if (p.x != q.x) return p.x < q.x;
	return p.y < q.y;
}

vector<P> convex_hull(P* ps, int n) {
	sort(ps, ps + n, cmp_x);
	int k = 0;
	vector<P> qs(n * 2);

	for (int i = 0; i < n; i++) {
		while (k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
		qs[k++] = ps[i];
	}

	int t = k;
	for (int i = n - 2; i >= 0; i--) {
		while (k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k - 1);
	return qs;
}

double dist(P p, P q) {
	return (p - q).dot(p - q);
}

int N;
P ps[50010];

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> ps[i].x >> ps[i].y;
	}

	vector<P> qs = convex_hull(ps, N);
	N = qs.size();
	if (N == 2) {
		cout << dist(qs[0], qs[1]) << endl;
		return 0;
	}

	int i = 0, j = 0;

	for (int k = 0; k < N; k++) {
		if (!cmp_x(qs[i], qs[k])) i = k;
		if (cmp_x(qs[j], qs[k])) j = k;
	}

	double res = 0;
	int si = i, sj = j;

	while (i != sj || j != si) {
		res = max(res, dist(qs[i], qs[j]));
		if ((qs[(i + 1) % N] - qs[i]).det(qs[(j + 1) % N] - qs[j]) < 0) {
			i = (i + 1) % N;
		}
		else {
			j = (j + 1) % N;
		}
	}

	cout << res << endl;

	return 0;
}