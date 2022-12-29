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
const int MAX_N = 50010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// 拡張ユークリッドの互除法
// a * x + b * y = gcd(a, b) の算出
// https://tbasic.org/reference/old/ExEuclid.html
long long extgcd(long long a, long long b, long long &x, long long &y) {
	long long d = a;
	if (b != 0) {
		d = extgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
	else {
		x = 1; y = 0;
	}
	return d;
}


int main() {

	long long a, b;
	long long x, y;
	cin >> a >> b;
	long long ans = extgcd(a, b, x, y);
	cout << ans << " " << x << " " << y << endl;

	return 0;

}