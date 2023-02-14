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


long long prime[MAX_N];
bool is_prime[MAX_N];

long long sieve(long long n) {
	long long p = 0;
	for (long long i = 0; i <= n; i++) {
		is_prime[i] = true;
	}
	is_prime[0] = is_prime[1] = false;
	for (long long i = 2; i <= n; i++) {
		if (is_prime[i]) {
			prime[p++] = i;
			for (long long j = 2 * i; j <= n; j += i) {
				is_prime[j] = false;
			}
		}
	}

	return p;
}

// Eratosthenes Range
// https://algo-method.com/tasks/332

bool is_prime_seg[MAX_N];
bool is_prime_seg_small[MAX_N];
// 範囲は [a, b)
void segment_sieve(long long a, long long b) {
	for (int i = 0; (long long)i * i < b; i++) {
		is_prime_seg_small[i] = true;
	}
	for (int i = 0; i < b - a; i++) {
		is_prime_seg[i] = true;
	}

	for (int i = 2; (long long)i * i < b; i++) {
		if (is_prime_seg_small[i]) {
			for (int j = 2 * i; (long long)j * j < b; j += i) {
				is_prime_seg_small[j] = false;
			}
			for (long long j = max(2LL, (a + i - 1) / i) * i; j < b; j += i) {
				is_prime_seg[j - a] = false;
			}
		}
	}
}

// Farey Sequence
// AOJ 2286
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2286
// https://ncastar.hatenablog.com/entry/20140320/1395323746
// https://qiita.com/hidekikangeki/items/e2524f199ae1d483f060
// 包除原理、オイラーのφ関数
// https://nanikaka.hatenadiary.org/entry/20111224/1324690802

long long euler[MAX_N];
long long answer[MAX_N];
void euler_phi2() {
	for (long long i = 0; i < MAX_N; i++) {
		euler[i] = i;
	}
	for (long long i = 2; i < MAX_N; i++) {
		if (euler[i] == i) {
			for (long long j = i; j < MAX_N; j += i) {
				euler[j] = euler[j] / i * (i - 1);
			}
		}
	}
}


int main() {

	// Eratosthenes
	long long N = sieve(100);
	cout << N << endl;
	for (long long i = 0; i < N; i++) {
		cout << prime[i] << " ";
	}
	cout << endl;

	// Eratosthenes Range
	long long A, B;
	cin >> A >> B;

	int ans = 0;
	segment_sieve(A, B + 1);
	for (int i = 0; i < B + 1 - A; i++) {
		if (is_prime_seg[i]) {
			ans++;
		}
	}
	cout << ans << endl;

	// Farey Sequence
	euler_phi2();
	answer[1] = 2;
	for (long long i = 2; i < MAX_N; i++) {
		answer[i] = answer[i - 1] + euler[i];
	}
	int T, M;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> M;
		cout << answer[M] << endl;
	}


	return 0;
}