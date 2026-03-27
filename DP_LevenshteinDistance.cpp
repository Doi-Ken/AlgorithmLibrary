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
const int MAX_N = 1000010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;


// https://nw.tsuda.ac.jp/lec/EditDistance/

string X;
string Y;
int dp[1010][1010];

int main() {
	
	cin >> X;
	cin >> Y;
	for (int x = 0; x <= X.length(); x++) {
		for (int y = 0; y <= Y.length(); y++) {
			dp[x][y] = INF;
		}
	}

	dp[0][0] = 0;
	for (int x = 0; x <= X.length(); x++) {
		dp[x][0] = x;
	}
	for (int y = 0; y <= Y.length(); y++) {
		dp[0][y] = y;
	}



	for (int x = 0; x < X.length(); x++) {
		for (int y = 0; y < Y.length(); y++) {
			
			dp[x + 1][y + 1] = min(dp[x + 1][y + 1], dp[x + 1][y] + 1);
			dp[x + 1][y + 1] = min(dp[x + 1][y + 1], dp[x][y + 1] + 1);

			if (X[x] == Y[y]) {
				dp[x + 1][y + 1] = min(dp[x + 1][y + 1], dp[x][y]);
			}
			else {
				dp[x + 1][y + 1] = min(dp[x + 1][y + 1], dp[x][y] + 1);
			}

		}
	}

	cout << dp[X.length()][Y.length()] << endl;


	return 0;
}