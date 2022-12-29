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
const int INF = 1000000000;
const long long LINF = 3e18 + 7;
const int MAX_N = 10010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// tribit
// https://atcoder.jp/contests/abc031/tasks/abc031_d
// ABC031 D

int T[20];

void convert_triset(int x) {
    int power3 = 1;
    for (int i = 0; i < 11; i++) {
        T[i] = 0;
    }
    for (int i = 0; i < 11; i++) {
        T[i] = (x / power3) % 3;
        power3 *= 3;
    }

    //for (int i = 0; i < 18; i++) {
    //    cout << T[i] << " ";
    //}
    //cout << endl;
}

int K, N;
string vt[52];
int v[52][12];
string w[52];

int main() {

    cin >> K >> N;

    for (int i = 0; i < N; i++) {
        cin >> vt[i] >> w[i];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < vt[i].length(); j++) {
            v[i][j] = (int)(vt[i][j] - '1');
        }
    }


    int ALL = pow(3, K);
    
    for (int n = 0; n < ALL; n++) {
        convert_triset(n);

        bool flag = true;

        for (int i = 0; i < N; i++) {
            int s = 0;
            for (int j = 0; j < vt[i].length(); j++) {
                s += (T[v[i][j]] + 1);
            }
            if (s != w[i].length()) {
                flag = false;
                break;
            }
        }

        if (flag) {
            break;
        }

    }

    map<int, string> m;

    for (int i = 0; i < N; i++) {

        int iter = 0;
        int s = 0;
        while (iter < w[i].length()) {
            if (m.find(v[i][s]) == m.end()) {
                m[v[i][s]] = w[i].substr(iter, (T[v[i][s]] + 1));
            }
            iter = iter + (T[v[i][s]] + 1);
            s++;
        }
    }

    for (int i = 0; i < K; i++) {
        cout << m[i] << endl;
    }
    

	return 0;
}