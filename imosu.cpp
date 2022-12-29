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


// https://imoz.jp/algorithms/imos_method.html
int table[MAX_N];
int T;
int C;
int S[MAX_N], E[MAX_N];

int main() {

	cin >> T >> C;
	for (int i = 0; i < C; i++) {
		cin >> S[i] >> E[i];
	}

	for (int i = 0; i < C; i++) {
		table[S[i]]++;  // 入店処理: カウントを 1 増やす
		table[E[i]]--;  // 出店処理: カウントを 1 減らす
	}
	
	// シミュレート
	for (int i = 0; i < T; i++) {
		if (0 < i) table[i] += table[i - 1];
	}
	
	// 最大値を調べる
	int M = 0;
	for (int i = 0; i < T; i++) {
		if (M < table[i]) M = table[i];
	}

	cout << M << endl;

	return 0;
}