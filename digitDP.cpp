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


// digit DP
// https://qiita.com/pinokions009/items/1e98252718eeeeb5c9ab
string str;
int a[110];
int dp[110][2][2]; // (上からi桁目までで条件を満たす数の総数)
int N;

int main() {

	cin >> N;
	cin >> str;

	for (int i = 0; i < N; i++) {
		a[i] = str[i] - '0';
	}
	
	dp[0][0][0] = 1;
	for (int i = 0; i < N; i++) {
		for (int smaller = 0; smaller < 2; smaller++) {
			for (int j = 0; j < 2; j++) {
				for (int x = 0; x <= (smaller ? 9 : a[i]); x++) {
					dp[i + 1][smaller || x < a[i]][j || x == 3] += dp[i][smaller][j];
				}
			}
		}
	}

	cout << dp[N][0][1] + dp[N][1][1] << endl;

	return 0;
}