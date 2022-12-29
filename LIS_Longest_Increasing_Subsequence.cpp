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
const int MAX_N = 7000010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// 最長増加部分列問題
// 蟻本 p. 63
// 長さnの数列 a0, a1, ..., an があります。この数列の増加部分列のうち、最長のものの長さを求めなさい。
// ただし、増加部分列とは、全てのi<jでai<ajを満たす部分列を言う。
// 5
// 4 2 3 1 5

int N;
int a[MAX_N];
int dp[MAX_N];


// dp[i] = 最後がa[i]であるような最長の増加部分列の長さ
// a[i]のみからなる列 or j < i かつ、aj < ai であるようなajで終わる増加部分列の後ろにaiを付け足した列
// のどちらか
// つまり、 dp[i] = max{1, dp[j] + 1 | j < i かつ aj < ai }
int solve() {
	int res = 0;
	for (int i = 0; i < N; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (a[j] < a[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		res = max(res, dp[i]);
	}

	return res;
}


// dp[i] = 長さが i+1 であるような増加部分列における最終要素の最小値（存在しない場合はINF）
// 詳細は蟻本 p. 65
int fastest_solve() {
	for (int i = 0; i < N; i++) {
		dp[i] = INF;
	}

	for (int i = 0; i < N; i++) {
		*lower_bound(dp, dp + N, a[i]) = a[i];
	}

	return lower_bound(dp, dp + N, INF) - dp;
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}

	cout << fastest_solve() << endl;


	return 0;
}