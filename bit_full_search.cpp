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


int N, M;
int a[MAX_N];

// n‚Å•\Œ»‚³‚ê‚éW‡‚É—v‘fi‚ªŠÜ‚Ü‚ê‚é‚©‚Ç‚¤‚©‚ğ”»’è‚µ‚ÄTrue/False‚ğ•Ô‚·ŠÖ”
bool has_bit(int n, int i) {
	return ((n & (1 << i)) > 0);
}

// input a[N] ‚©‚çM‚ğì¬‚Å‚«‚é‚©‚Ç‚¤‚©
int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}

	int ALL = 1 << N;

	for (int n = 0; n < ALL; n++) {
		int sum = 0;
		for (int i = 0; i < N; i++) {
			if (has_bit(n, i)) {
				sum += a[i];
			}
		}
		if (sum == M) {
			cout << "Yes" << endl;
			return 0;
		}
	}

	cout << "No" << endl;

	return 0;
}