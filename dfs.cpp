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

int N;
int a[100];
int K;


bool dfs(int i, int sum) {
	if (i == N) return sum == K;

	if (dfs(i + 1, sum)) {
		return true;
	}
	if(dfs(i + 1, sum + a[i])) {
		return true;
	}
	return false;
	
}


int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}
	cin >> K;

	if (dfs(0, 0)) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	return 0;
}