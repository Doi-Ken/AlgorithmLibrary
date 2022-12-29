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
const int MAX_N = 600010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;


long long par[MAX_N];
long long rank1[MAX_N];
long long siz[MAX_N];

void init(long long n) {
	for (long long i = 0; i < n; i++) {
		par[i] = i;
		rank1[i] = 0;
		siz[i] = 1;
	}
}

long long find(long long x) {
	if (par[x] == x) {
		return x;
	}
	else {
		return par[x] = find(par[x]);
	}
}

void unite(long long x, long long y) {
	x = find(x);
	y = find(y);
	if (x == y) return;

	if (rank1[x] < rank1[y]) {
		par[x] = y;
		siz[y] += siz[x];
	}
	else {
		par[y] = x;
		siz[x] += siz[y];
		if (rank1[x] == rank1[y]) rank1[x]++;
	}
}

bool same(long long x, long long y) {
	return find(x) == find(y);
}

long long usize(long long x) {
	return siz[find(x)];
}

int main() {

	init(10);
	unite(1, 3);
	unite(3, 5);
	unite(2, 4);
	unite(3, 7);

	cout << 1 << " " << 7 << " " << same(1, 7) << endl;
	cout << 2 << " " << 7 << " " << same(2, 7) << endl;
	cout << 2 << " " << 4 << " " << same(2, 4) << endl;

	for (int i = 0; i < 10; i++) {
		cout << usize(i) << " ";
	}
	cout << endl;

	return 0;
}