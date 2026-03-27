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

// p. 163 BIT generalization
// POJ 3468

long long N;
long long bit0[2 * MAX_N - 1];
long long bit1[2 * MAX_N - 1];

void add(long long *b, int i, long long v) {
	
	while (i <= N) {
		b[i] += v;
		i += i & -i;
	}

}

long long sum(long long *b, int i) {

	long long s = 0;
	while (i > 0) {
		s += b[i];
		i -= i & -i;
	}
	return s;
}

// [f, t] (only one bit)
long long sum(long long* b, int f, int t) {
	return sum(b, t) - sum(b, f - 1);
}

// [0, n] (two bit sum)
long long sum(int i) {
	return sum(bit1, i) * i + sum(bit0, i);
}

// [l, n] (two bit sum)
long long range_sum(int l, int r) {
	return sum(r) - sum(l - 1);
}

// [l, r] (two bit sum)
void range_add(int l, int r, long long x) {
	add(bit0, l, -x * (l - 1));
	add(bit1, l, x);
	add(bit0, r + 1, x * r);
	add(bit1, r + 1, -x);
}

int Q;
long long L[MAX_N], R[MAX_N];
long long X[MAX_N];
char T[MAX_N];
long long A[MAX_N];

int main() {

	cin >> N >> Q;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
	}

	for (int q = 0; q < Q; q++) {
		cin >> T[q];
		if (T[q] == 'Q') {
			cin >> L[q] >> R[q];
		}
		else {
			cin >> L[q] >> R[q] >> X[q];
		}
	}

	for (long long i = 1; i <= N; i++) {
		add(bit0, i, A[i]);
	}

	for (int i = 0; i < Q; i++) {
		if (T[i] == 'Q') {
			long long res = 0;
			res += sum(bit0, R[i]) + sum(bit1, R[i]) * R[i];
			res -= sum(bit0, L[i] - 1) + sum(bit1, L[i] - 1) * (L[i] - 1);
			cout << res << endl;
		}
		else {

			add(bit0, L[i], -X[i] * (L[i] - 1));
			add(bit1, L[i], X[i]);
			add(bit0, R[i] + 1, X[i] * R[i]);
			add(bit1, R[i] + 1, -X[i]);
		}
	}


	return 0;
}