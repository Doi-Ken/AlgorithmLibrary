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
const long long LINF = 1e18 + 7;
const int MAX_N = 1200010;
const int MAX_W = 600010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long; 


// 蟻本 p.179
// ドミノ敷き詰め
// https://www.slideshare.net/slideshow/advanced-dp-2016/64479125
// https://hcpc-hokudai.github.io/archive/dynamic_programming_002.pdf

// 3 3
// ...
// .x.
// ...

int N, M;
string S[20];
bool color[20][20];
int dp[2][1 << 20];
int mod = 1000000;

bool has_bit(int n, int i) {
    return (n & (1 << i)) > 0;
}

int main() {

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (S[i][j] == 'x') {
                color[i][j] = true;
            }
            else {
                color[i][j] = false;
            }
        }
    }

    int* crt = dp[0];
    int* next = dp[1];

    crt[0] = 1;
    for (int i = N - 1; i >= 0; i--) {
        for (int j = M - 1; j >= 0; j--) {
            for (int used = 0; used < (1 << M); used++) {
                if (has_bit(used, j) || color[i][j]) {
                    // (i, j)にはブロックを置く必要がない
                    next[used] = crt[used & ~(1 << j)];
                }
                else {
                    // 2通りの向きを試す
                    int res = 0;

                    // 横向き
                    if (j + 1 < M && !has_bit(used, j + 1) && !color[i][j + 1]) {
                        res += crt[used | (1 << (j + 1))];
                    }

                    // 縦向き
                    if (i + 1 < N && !color[i + 1][j]) {
                        res += crt[used | (1 << j)];
                    }
                    next[used] = res % mod;
                }
            }
            swap(crt, next);
        }
    }
    cout << crt[0] << endl;
    
    return 0;
}