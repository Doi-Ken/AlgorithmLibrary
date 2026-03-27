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
const int MAX_N = 200010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// lowlink (Articulation Point)
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=ja
// https://algo-logic.info/articulation-points/

struct Edge {
    int to;
};
typedef vector<vector<Edge> > Graph;
typedef pair<long, long> P;

/* Lowlink: グラフの関節点・橋を列挙する構造体
    作成: O(E+V)
    関節点の集合: vector<int> aps
    橋の集合: vector<P> bridges
*/
struct LowLink {
    const Graph& G;
    vector<int> used, ord, low;
    vector<int> aps;  // articulation points
    vector<P> bridges;

    LowLink(const Graph& G_) : G(G_) {
        used.assign(G.size(), 0);
        ord.assign(G.size(), 0);
        low.assign(G.size(), 0);
        int k = 0;
        for (int i = 0; i < (int)G.size(); i++) {
            if (!used[i]) k = dfs(i, k, -1);
        }
        sort(aps.begin(), aps.end()); // 必要ならソートする
        sort(bridges.begin(), bridges.end()); // 必要ならソートする
    }

    int dfs(int id, int k, int par) { // id:探索中の頂点, k:dfsで何番目に探索するか, par:idの親
        used[id] = true;
        ord[id] = k++;
        low[id] = ord[id];
        bool is_aps = false;
        int count = 0; // 子の数
        for (int j = 0; j < G[id].size();j++) {
            Edge e = G[id][j];
            if (!used[e.to]) {
                count++;
                k = dfs(e.to, k, id);
                low[id] = min(low[id], low[e.to]);
                if (par != -1 && ord[id] <= low[e.to]) is_aps = true; // 条件2を満たすので関節点
                if (ord[id] < low[e.to]) bridges.push_back(P(min(id, e.to), max(id, e.to)));
            }
            else if (e.to != par) { // eが後退辺の時
                low[id] = min(low[id], ord[e.to]);
            }
        }
        if (par == -1 && count >= 2) is_aps = true; // 条件1を満たすので関節点
        if (is_aps) aps.push_back(id);
        return k;
    }
};


int main() {

    int N, E;
    cin >> N >> E;

    Graph graph(N);

    for (int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        Edge e1;
        e1.to = b;
        Edge e2;
        e2.to = a;
        graph[a].push_back(e1);
        graph[b].push_back(e2);
    }

    LowLink l = LowLink(graph);

    vector<int> v = l.aps;

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
    
	return 0;
}