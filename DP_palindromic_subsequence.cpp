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
const int INF = 1000000007;
const long long LINF = 3e18 + 7;
const int MAX_N = 1200010;
const int MAX_W = 600010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long; 

// Palindromic Subsequenece
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2895
// https://qiita.com/drken/items/a207e5ae3ea2cf17f4bd

long long mod = 1000000007;

vector<vector<long long> > calcNext(string S) {
    int n = S.size();
    vector<vector<long long> > res(n + 1, vector<long long>(26, n));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            res[i][j] = res[i + 1][j];
        }
        res[i][S[i] - 'a'] = i;
     }

    return res;
}


int main() {
    
    string S;
    cin >> S;
    
    int n = S.size();

    string T = S;
    reverse(T.begin(), T.end());

    vector<vector<long long> > ns = calcNext(S);
    vector<vector<long long> > nt = calcNext(T);
    vector<vector<long long> > dp(n + 1, vector<long long>(n + 1, 0));

    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 26; k++) {
                int ni = ns[i][k];
                int nj = nt[j][k];

                if (ni + nj + 2 > n) continue;
                dp[ni + 1][nj + 1] += dp[i][j];
                dp[ni + 1][nj + 1] %= mod;
            }
        }

    }

    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; i + j <= n; j++) {
            int num = 1;
            for (int k = 0; k < 26; k++) {
                if (ns[i][k] + 1 + j <= n) {
                    num++; // 奇数長の回文の時の文字の数を足す
                }
            }
            ans = (ans + dp[i][j] * num % mod) % mod;
        }
    }

    cout << ans - 1 << endl;

    
    return 0;
}