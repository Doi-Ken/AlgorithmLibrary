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
const int INF = 10000000000;
const long long LINF = 3e18 + 7;
const int MAX_N = 20010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// 連鎖行列積
// https://qiita.com/ikamirin/items/5ddbe04cb4d4ce6ed6af
// https://www.jaist.ac.jp/~uehara/course/2010/i431/pdf/10matrix.pdf 10ページ
// https://algorithmbeginner.blogspot.com/2019/10/blog-post.html
int N;
int M[MAX_N][2];
int dp[MAX_N][MAX_N];

int main() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> M[i][0] >> M[i][1];
	}

	for (int i = 0; i < N; i++) {
		dp[i][i] = 0;
	}

	for (int d = 1; d < N; d++) {
		for (int i = 0; i < N - d; i++) {
			int j = i + d;
			dp[i][j] = INF;
			for (int k = i; k < j; k++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + M[i][0] * M[k][1] * M[j][1]);
			}
		}
	}

	cout << dp[0][N - 1] << endl;

	return 0;
}