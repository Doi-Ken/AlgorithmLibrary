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

int main() {
	long long mod = 1000000007;
	long long x, n;
	cin >> x >> n;

	cout << mod_pow(x, n, mod) << endl;

	return 0;
}