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
const int MAX_N = 20010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

long long W, H;

// https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a
// combination (W+H)_C_H
// ‹a–{ p.114
// x^n % mod
long long mod_pow(long long x, long long n, long long mod) {
	long long res = 1;
	while (n > 0) {
		if (n & 1) {
			res = ((res * x) % mod);
		}
		x = ((x * x) % mod);
		n >>= 1;
	}

	return res;
}

// l_C_r % mod;
long long combination(long long l, long long r, long long mod) {
	long long ans = 1;

	for (long long i = 1; i <= r; i++) {
		int value = l - (i - 1);
		ans = (ans * value % mod);
	}
	for (long long i = 2; i <= r; i++) {
		// axß1 (mod p) ‚Ì‰ðx‚Í a^(p-2) mod p ‚Æ‚È‚éBip‚ª‘f”‚Ìê‡j
		long long m = mod_pow(i, mod - 2, mod);
		ans = ((ans * m) % mod);
	}

	return ans;
}

// https://qiita.com/mosamosa/items/79cf230ae22ee71f6801
std::vector<std::vector<long long>> comb(long long n, long r) {
	std::vector<std::vector<long long>> v(n + 1, std::vector<long long>(n + 1, 0));
	for (int i = 0; i < v.size(); i++) {
		v[i][0] = 1;
		v[i][i] = 1;
	}
	for (int j = 1; j < v.size(); j++) {
		for (int k = 1; k < j; k++) {
			v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
		}
	}
	return v;
}


int main() {

	long long mod = 1000000007;
	cin >> W >> H;

	long long WH = H + W;

	cout << combination(WH, H, mod) << endl;

	vector<vector<long long>> com = comb(51, 51);
	
	cout << com[50][25] << endl;


	return 0;
}