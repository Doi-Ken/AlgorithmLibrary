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

// https://www.796t.com/content/1549561877.html

int G[510][510];
int w[510], v[510];
bool vis[510];
int N, M;

int sw(int n) {
    int min_cut = INF;
    for (int i = 0; i < n; i++) v[i] = i;
    while (n > 1)
    {
        int pre = 0;
        memset(vis, false, sizeof(vis));
        memset(w, 0, sizeof(w));
        for (int i = 1; i < n; i++)
        {
            int k = -1;
            for (int j = 1; j < n; j++)
            {
                if (vis[v[j]]) continue;
                w[v[j]] += G[v[pre]][v[j]];
                if (k == -1 || w[v[k]] < w[v[j]])
                {
                    k = j;
                }
            }
            vis[v[k]] = true;
            if (i == n - 1)
            {
                int s = v[pre], t = v[k];
                min_cut = min(min_cut, w[t]);
                for (int j = 0; j < n; j++)
                {
                    G[s][v[j]] += G[t][v[j]];
                    G[v[j]][s] += G[v[j]][t];
                }
                v[k] = v[--n];
            }
            pre = k;
        }
    }
    return min_cut;
}


int main() {

    int N, M;
    while (scanf("%d %d\n", &N, &M) != EOF) {

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                G[i][j] = 0;
            }
        }
        for (int i = 0; i < M; i++) {
            int a, b, c;
            scanf("%d %d %d\n", &a, &b, &c);
            G[a][b] += c;
            G[b][a] += c;
        }
        int min_cut = sw(N);
        printf("%d\n", min_cut);
    }
    return 0;
}