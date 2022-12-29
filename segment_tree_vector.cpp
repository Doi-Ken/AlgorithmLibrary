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

// p. 171 segment tree vector
// POJ 2104

int N, M;
long long A[MAX_N];
int I[MAX_N], J[MAX_N], K[MAX_N];
long long nums[MAX_N];
vector<long long> dat[MAX_N];

// セグメント木を構築する
// kは節点の番号で区間[l, r)に対応
void init(int k, int l, int r) {
	if (r - l == 1) {
		dat[k].push_back(A[l]);
	}
	else {
		int lch = 2 * k + 1;
		int rch = 2 * k + 2;

		init(lch, l, (l + r) / 2);
		init(rch, (l + r) / 2, r);
		dat[k].resize(r - l);

		merge(dat[lch].begin(), dat[lch].end(), dat[rch].begin(), dat[rch].end(), dat[k].begin());
	}
}

// [i, j) のx以下の数の個数を数える
// kは節点の番号で区間[l, r)に対応
int query(int i, int j, long long x, int k, int l, int r) {
	if (j <= l || r <= i) {
		return 0;
	}
	else if (i <= l && r <= j) {
		return upper_bound(dat[k].begin(), dat[k].end(), x) - dat[k].begin();
	}
	else {
		int lc = query(i, j, x, k * 2 + 1, l, (l + r) / 2);
		int rc = query(i, j, x, k * 2 + 2, (l + r) / 2, r);
		return lc + rc;
	}
}


int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < M; i++) {
		cin >> I[i] >> J[i] >> K[i];
		I[i]--;
		J[i]--;
	}

	for (int i = 0; i < N; i++) {
		nums[i] = A[i];
	}
	sort(nums, nums + N);

	init(0, 0, N);

	for (int i = 0; i < M; i++) {
		int l = I[i];
		int r = J[i] + 1;
		int k = K[i];

		int lb = -1;
		int ub = N - 1;

		while (ub - lb > 1) {
			int mid = (ub + lb) / 2;
			int c = query(l, r, nums[mid], 0, 0, N);
			if (c >= k) {
				ub = mid;
			}
			else {
				lb = mid;
			}
		}

		cout << nums[ub] << endl;

	}

	return 0;
}