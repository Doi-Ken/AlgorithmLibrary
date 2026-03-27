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
int a[MAX_N];
int s[MAX_N + 1];

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}

	for (int i = 0; i < N; i++) {
		s[i + 1] = s[i] + a[i];
	}

	for (int i = 0; i < N + 1; i++) {
		cout << s[i] << " ";
	}
	cout << endl;

	return 0;
}