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
const int MAX_N = 50010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// binary_indexed_tree 2d
// POJ 2155 
// https://algo-logic.info/binary-indexed-tree/#toc_id_4_5
// https://blue-jam.hatenablog.com/entry/2014/09/08/231104

int N, X, Y;

/* BIT2D:
    初期値は全て 0
    ・add(h,w,x): (h,w) に x を加算する
    ・sum(h,w): 1≦i≦h かつ 1≦j≦w の範囲の合計値を求める
    ・query(h1,w1,h2,w2): h1≦i<h2 かつ w1≦j<w2 の範囲の合計値を求める(1-indexed)
    計算量は全て O(logW * logH)
*/
template <typename T>
struct BIT2D {
    int H, W;
    vector<vector<T>> bit;  // データの格納先
    BIT2D(int H_, int W_) { init(H_, W_); }
    void init(int H_, int W_) {
        H = H_ + 1;
        W = W_ + 1;
        bit.assign(H, vector<T>(W, 0));
    }

    void add(int h, int w, T x) {
        for (int i = h; i < H; i += (i & -i)) {
            for (int j = w; j < W; j += (j & -j)) {
                bit[i][j] += x;
            }
        }
    }
    // 1≦i≦h かつ 1≦j≦w
    T sum(int h, int w) {
        T s(0);
        for (int i = h; i > 0; i -= (i & -i)) {
            for (int j = w; j > 0; j -= (j & -j)) {
                s += bit[i][j];
            }
        }
        return s;
    }

    // h1≦i<h2 かつ w1≦j<w2
    T query(int h1, int w1, int h2, int w2) {
        return sum(h2 - 1, w2 - 1) - sum(h2 - 1, w1 - 1) - sum(h1 - 1, w2 - 1) + sum(h1 - 1, w1 - 1);
    }
};


int T;
int M, Q;
char q[MAX_N];
int X1[MAX_N], Y1[MAX_N], X2[MAX_N], Y2[MAX_N];

int main() {

    
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> M >> Q;
        BIT2D<long long> bit(M, M);

        for (int i = 0; i < Q; i++) {
            cin >> q[i] >> X1[i] >> Y1[i];
            if (q[i] == 'C') {
                cin >> X2[i] >> Y2[i];
            }
        }

        for (int i = 0; i < Q; i++) {
            if (q[i] == 'Q') {
                long long ans = bit.sum(Y1[i], X1[i]);
                cout << ans % 2 << endl;
            }
            else {
                bit.add(Y1[i], X1[i], 1);
                bit.add(Y2[i] + 1, X1[i], 1);
                bit.add(Y1[i], X2[i] + 1, 1);
                bit.add(Y2[i] + 1, X2[i] + 1, 1);
            }
        }
        cout << endl;

    }
	
	
	return 0;
}