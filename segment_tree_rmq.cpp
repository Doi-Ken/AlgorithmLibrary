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

// k�Ԗڂ̒l (0-indexed) ��a�ɕύX
void update(int k, long long a) {
	
	// �t�̐ߓ_ (��ԍŉ��w�̃m�[�h�� N - 1 + k �Ԗڂŕێ����Ă���B(�P�ԉ��̑w�ȊO�� N - 1��))
	k += N - 1;
	dat[k] = a;

	while (k > 0) {
		k = (k - 1) / 2;
		dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
	}
}

// [a, b) �̍ŏ��l�����߂�
// k �͐ߓ_�̔ԍ��Al, r�͂��̐ߓ_��[l, r)�ɑΉ��Â��Ă��邱�Ƃ�\���B
// ���������āA�O����query(a, b, 0, 0, n)����ԁB
// (k(0)�Ԗڂ̐ߓ_�Al(0) �` r(n)�̊Ԃ����߂͎w��)
long long query(int a, int b, int k, int l, int r) {

	// [a, b)��[l, r)���������Ȃ���� INF
	if (r <= a || b <= l) {
		return LINF;
	}

	// [a, b) ��[l, r)�����S�Ɋ܂�ł���΁A���̐ߓ_�̒l
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