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
const int MAX_N = 20010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

int W, H, N;
int X1[MAX_N], X2[MAX_N], Y1[MAX_N], Y2[MAX_N];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

bool field[MAX_N][MAX_N];

// p.150 compress
//10 10 5
//1 1 4 9 10
//6 10 4 9 10
//4 8 1 1 6
//4 8 10 5 10


// X1, X2Çç¿ïWà≥èkÇµÅAç¿ïWà≥èkÇµÇΩç€ÇÃïùÇï‘Ç∑

int compress(int* x1, int* x2, int w) {
	vector<int> xs;

	for (int i = 0; i < N; i++) {
		for (int d = -1; d <= 1; d++) {
			int tx1 = x1[i] + d;
			int tx2 = x2[i] + d;

			if (0 <= tx1 && tx1 < w) {
				xs.push_back(tx1);
			}
			if (0 <= tx2 && tx2 < w) {
				xs.push_back(tx2);
			}

		}
	}

	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());

	for (int i = 0; i < N; i++) {
		x1[i] = find(xs.begin(), xs.end(), x1[i]) - xs.begin();
		x2[i] = find(xs.begin(), xs.end(), x2[i]) - xs.begin();
	}

	return xs.size();
}

int compress(int p[]) {
	vector<int> ps;
	ps.resize(N);
	for (int i = 0; i < N; ++i) {
		ps[i] = p[i];
	}
	sort(ps.begin(), ps.end());
	ps.erase(unique(ps.begin(), ps.end()), ps.end());
	for (int i = 0; i < N; ++i) {
		p[i] = 2 + (int)distance(ps.begin(), lower_bound(ps.begin(), ps.end(), p[i]));
	}
	return 2 + (int)ps.size();
}

int main() {


	cin >> W >> H >> N;

	for (int i = 0; i < N; i++) {
		cin >> X1[i];
		X1[i]--;
	}
	for (int i = 0; i < N; i++) {
		cin >> X2[i];
		X2[i]--;
	}
	for (int i = 0; i < N; i++) {
		cin >> Y1[i];
		Y1[i]--;
	}
	for (int i = 0; i < N; i++) {
		cin >> Y2[i];
		Y2[i]--;
	}

	W = compress(X1, X2, W);
	H = compress(Y1, Y2, H);
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			field[i][j] = false;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int y = Y1[i]; y <= Y2[i]; y++) {
			for (int x = X1[i]; x <= X2[i]; x++) {
				field[y][x] = true;
			}
		}
	}

	int ans = 0;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			if (field[y][x]) {
				continue;
			}
			ans++;

			queue<pair<int, int> > que;
			que.push(make_pair(y, x));
			while (!que.empty()) {
				int sy = que.front().first;
				int sx = que.front().second;

				que.pop();

				for (int i = 0; i < 4; i++) {
					int tx = sx + dx[i];
					int ty = sy + dy[i];

					if (tx >= 0 && tx < W && ty >= 0 && ty < H && !field[ty][tx]) {
						que.push(make_pair(ty, tx));
						field[ty][tx] = true;
					}
				}
			}

		}
	}

	cout << ans << endl;

	return 0;
}