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



// �傫�� N �~ M�̒낪����A�J���~���Đ����܂肪�ł����B
// �����܂��8�ߖT�Őڂ��Ă���ꍇ�Ɍq�����Ă���Ƃ���
// �S���ł����̐����܂肪���邩
// 'W'�������܂� '.' �������܂�łȂ�
// sample
// 10 12
// W........WW.
// .WWW.....WWW
// ....WW...WW.
// .........WW.
// .........W..
// ..W......W..
// .W.W.....WW.
// W.W.W.....W.
// .W.W......W.
// ..W.......W.
// answer: 3

char field[MAX_W][MAX_W];
int N, M;

void dfs(int y, int x) {
	field[y][x] = '.';

	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			int nx = x + dx;
			int ny = y + dy;
			if (nx >= 0 && nx < M && ny >= 0 && ny < N && field[ny][nx] == 'W') {
				dfs(ny, nx);
			}
		}
	}
	
}

int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> field[i][j];
		}
	}
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field[i][j] == 'W') {
				ans++;
				dfs(i, j);
			}
		}
	}

	cout << ans << endl;

	return 0;
}