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
const int MAX_N = 2000010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// Baby-step giant-step algorithm 離散対数
// https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a

// a^b
long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}


// a^-1
long long modinv(long long a, long long m) {
    long long b = m, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m;
    if (u < 0) u += m;
    return u;
}

// a^x ≡ b (mod. m) となる最小の正の整数 x を求める
long long modlog(long long a, long long b, int m) {
    a %= m, b %= m;

    // calc sqrt{M}
    long long lo = -1, hi = m;
    while (hi - lo > 1) {
        long long mid = (lo + hi) / 2;
        if (mid * mid >= m) hi = mid;
        else lo = mid;
    }
    long long sqrtM = hi;

    // {a^0, a^1, a^2, ..., a^sqrt(m)} 
    map<long long, long long> apow;
    long long amari = a;
    for (long long r = 1; r < sqrtM; ++r) {
        if (!apow.count(amari)) apow[amari] = r;
        (amari *= a) %= m;
    }

    // check each A^p
    long long A = modpow(modinv(a, m), sqrtM, m);
    amari = b;
    for (long long q = 0; q < sqrtM; ++q) {
        if (amari == 1 && q > 0) return q * sqrtM;
        else if (apow.count(amari)) return q * sqrtM + apow[amari];
        (amari *= A) %= m;
    }

    // no solutions
    return -1;
}


int main() {

    // 使い方の一例: a <= 10, b <= 10 に対して計算してみる
    const int MOD = 1000000007;
    for (long long a = 2; a <= 10; ++a) {
        for (long long b = 1; b <= 10; ++b) {
            cout << "log_" << a << "(" << b << ") = " << modlog(a, b, MOD) << endl;
        }
    }



	return 0;
}