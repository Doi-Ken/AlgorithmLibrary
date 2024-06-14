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

// https://qiita.com/drken/items/a207e5ae3ea2cf17f4bd

const int MOD = 1000000007;

// res[i][c] := i 文字目以降で最初に文字 c が登場する index (存在しないときは n)
vector<vector<int> > calcNext(const string& S) {
    int n = (int)S.size();
    vector<vector<int> > res(n + 1, vector<int>(26, n));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) res[i][j] = res[i + 1][j];
        res[i][S[i] - 'a'] = i;
    }
    return res;
}

// mod 1000000007 の世界で a += b する関数
void add(long long& a, long long b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int main() {
    // 入力
    string S; cin >> S;
    int n = (int)S.size();

    // 前処理配列
    vector<vector<int> > next = calcNext(S);

    // DP
    vector<long long> dp(n + 1, 0);
    dp[0] = 1; // 初期化、空文字列 "" に対応
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (next[i][j] >= n) continue; // 次の文字 j がもうない場合はスルー
            add(dp[next[i][j] + 1], dp[i]);
        }
    }

    // 集計
    long long res = 0;
    for (int i = 0; i <= n; ++i) add(res, dp[i]);

    cout << res << endl;


    return 0;

}
