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
const int MAX_N = 600010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// https://qiita.com/drken/items/ecd1a472d3a0e7db8dce
long long N, Q;
long long a[MAX_N];
long long x[MAX_N];

int main() {

	cin >> N >> Q;

	for (long long i = 0; i < N; i++) {
		cin >> a[i];
	}

	for (long long i = 0; i < Q; i++) {
		cin >> x[i];
	}

	for (long long q = 0; q < Q; q++) {
		long long res = 0;
		long long right = 0;
		long long sum1 = 0;
		for (long long left = 0; left < N; left++) {

			/* sum1 に a[right] を加えても大丈夫なら right を動かす */
			while (right < N && sum1 + a[right] <= x[q]) {
				sum1 += a[right];
				right++;
			}

			/* break した状態で right は条件を満たす最大 */
			res += (right - left);

			/* left をインクリメントする準備 */
			if (right == left) { // right が left に重なったら right も動かす
				right++;
			}
			else {
				sum1 -= a[left]; // left のみがインクリメントされるので sum1 から a[left] を引く
			}
		}
		cout << res << endl;

	}

	return 0;
}