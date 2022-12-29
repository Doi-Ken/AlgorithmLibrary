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
const int MAX_N = 6000010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// bfs
// 大きさがN × Mの迷路で上下左右4マスの通路に移動できる。
// スタートからゴールまで移動するのに最小のターン数を求める。
// sample
// 10 10
// #S######.#
// ......#..#
// .#.##.##.#
// .#........
// ##.##.####
// ....#....#
// .#######.#
// ....#.....
// .####.###.
// ....#...G#

char field[MAX_W][MAX_W];
int steps[MAX_W][MAX_W];
int N, M;
int sx, sy;
int gx, gy;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int bfs(int sy, int sx, int gy, int gx) {

	steps[sy][sx] = 0;
	queue<pair<int, int>> que;
	que.push(make_pair(sy, sx));


	while (!que.empty()) {
		int y = que.front().first;
		int x = que.front().second;
		que.pop();
		if (x == gx && y == gy) {
			return steps[y][x];
		}
		
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= 0 && nx < M && ny >= 0 && ny < N && steps[ny][nx] == -1 && field[ny][nx] != '#') {
				steps[ny][nx] = steps[y][x] + 1;
				que.push(make_pair(ny, nx));
			}
		}
	}

	return -1;

}

int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> field[i][j];
			if (field[i][j] == 'S') {
				sx = j;
				sy = i;
			}
			if (field[i][j] == 'G') {
				gx = j;
				gy = i;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			steps[i][j] = -1;
		}
	}

	int ans = bfs(sy, sx, gy, gx);

	cout << ans << endl;

	return 0;
}