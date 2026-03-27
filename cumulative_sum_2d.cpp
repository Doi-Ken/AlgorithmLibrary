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

int N;
int H, W, Q;
int a[MAX_W][MAX_W];
int s[MAX_W + 1][MAX_W + 1];

int main() {

	cin >> H >> W;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> a[i][j];
		}
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + a[i][j];
		}
	}

	cin >> Q;
	for (int q = 0; q < Q; q++) {
		int x1, x2, y1, y2;
		cin >> y1 >> y2 >> x1 >> x2;
		cout << s[y2][x2] - s[y1][x2] - s[y2][x1] + s[y1][x1] << endl;
	}


	return 0;
}