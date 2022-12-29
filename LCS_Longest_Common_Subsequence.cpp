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
const int MAX_N = 60010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

/// <summary>
/// ç≈í∑ã§í ïîï™óÒ(LCS)ñ‚ëË
/// https://qiita.com/drken/items/a5e6fe22863b7992efdb#%E5%95%8F%E9%A1%8C-8%E6%9C%80%E9%95%B7%E5%85%B1%E9%80%9A%E9%83%A8%E5%88%86%E5%88%97-lcs-%E5%95%8F%E9%A1%8C
/// 
/// dp[i+1][j+1]={ max(dp[i][j]+1,dp[i+1][j],dp[i][j+1]) } (S[i]==T[j])
/// dp[i + 1][j + 1] = { max(dp[i + 1][j],dp[i][j + 1]) } (S[i] != T[j])
/// 
/// </summary>

int dp[MAX_W][MAX_W];
int Q;

int main() {

	string X, Y;
	cin >> X;
	cin >> Y;
	

	for (int i = 0; i <= X.size(); i++) {
		for (int j = 0; j <= Y.size(); j++) {
			dp[i][j] = 0;
		}
	}

	for (int i = 0; i < X.size(); i++) {
		for (int j = 0; j < Y.size(); j++) {
			if (X[i] == Y[j]) { 
				dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 1); 
			}

			dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i + 1][j]);
			dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j + 1]);
		}
	}
	cout << dp[X.size()][Y.size()] << endl;

	

	return 0;
}