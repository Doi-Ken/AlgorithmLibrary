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

// p. 161 BIT (https://www.slideshare.net/hcpc_hokudai/binary-indexed-tree)
// (BIT[] 自体は1-index)
int N;
long long bit[MAX_N + 1];

long long sum(int i) {
	long long s = 0;
	while (i > 0) {
		s += bit[i];
		i -= i & -i;
	}
	return s;
}

void add(int i, long long x) {
	while (i <= N) {
		bit[i] += x;
		i += i & -i;
	}
}

// p. 162 Example (バブルソートのスワップ回数)
long long a[MAX_N];


int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}
	long long ans = 0;

	for (long long i = 0; i < N; i++) {
		ans += (i - sum(a[i]));
		add(a[i], 1);
	}

	cout << ans << endl;

	return 0;
}