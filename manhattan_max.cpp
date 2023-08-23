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
const int INF = 1000000000;
const long long LINF = 3e18 + 7;
const int MAX_N = 5000010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// Max Manhattan Distance
// https://atcoder.jp/contests/abc178/tasks/abc178_e
// 参考問題
// https://atcoder.jp/contests/typical90/tasks/typical90_aj
// https://blog.hamayanhamayan.com/entry/2017/10/03/165802

int N;
typedef pair<long long, long long> P;

P xy[MAX_N];
P uv[MAX_N];

bool comp_x(P& p1, P& p2) {
	return p1.first < p2.first;
}
bool comp_y(P& p1, P& p2) {
	return p1.second < p2.second;
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> xy[i].first >> xy[i].second;
	}
	for (int i = 0; i < N; i++) {
		uv[i].first = xy[i].first + xy[i].second;
		uv[i].second = xy[i].first - xy[i].second;
	}

	sort(uv, uv + N, comp_x);

	long long max_x = uv[N - 1].first - uv[0].first;

	sort(uv, uv + N, comp_y);

	long long max_y = uv[N - 1].second - uv[0].second;

	cout << max(max_x, max_y) << endl;

	return 0;
}