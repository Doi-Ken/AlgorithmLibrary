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
#include <chrono>
#include <random>
using namespace std;
const int INF = 100000000;
const long long LINF = 1e18 + 7;
const int MAX_N = 5000010;
const int MAX_W = 1102;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
using ll = long long;


// https://ysugiyama.hatenablog.com/entry/2018/10/31/233418

template <typename Iterator>
inline bool next_combination(const Iterator first, Iterator k, const Iterator last)
{
    /* Credits: Thomas Draper */
    if ((first == last) || (first == k) || (last == k))
        return false;
    Iterator itr1 = first;
    Iterator itr2 = last;
    ++itr1;
    if (last == itr1)
        return false;
    itr1 = last;
    --itr1;
    itr1 = k;
    --itr2;
    while (first != itr1)
    {
        if (*--itr1 < *itr2)
        {
            Iterator j = k;
            while (!(*itr1 < *j)) ++j;
            iter_swap(itr1, j);
            ++itr1;
            ++j;
            itr2 = k;
            rotate(itr1, j, last);
            while (last != j)
            {
                ++j;
                ++itr2;
            }
            rotate(k, itr2, last);
            return true;
        }
    }
    rotate(first, k, last);
    return false;
}

int main() {


    ll N, K;
    cin >> N >> K;
    vector<ll> v(N);
    for (int i = 0; i < N; i++) {
        v[i] = i;
    }
    do {
        for (int i = 0; i < K; i++) {
            cout << v[i] << " ";
        }
        cout << endl;

    } while (next_combination(v.begin(), v.begin() + K, v.end()));
}