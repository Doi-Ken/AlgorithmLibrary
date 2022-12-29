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
const int INF = 1000000000;
const long long LINF = 3e18 + 7;
const int MAX_N = 50010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;



vector<long long> divisor(long long n) {
	vector<long long> res;
	for (long long i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			res.push_back(i);
			if (i != n / i) res.push_back(n / i);
		}
	}
	return res;
}

int F[MAX_N];

void calcNumDiv(int n) {
	fill(F, F + n + 1, 1);
	for (int i = 2; i <= n; ++i) if (F[i] == 1) {
		for (int j = i; j <= n; j += i) {
			int k = 0;
			for (int m = j; m % i == 0; m /= i, ++k);
			F[j] *= k + 1;
		}
	}
}


int main() {

	vector<long long> v = divisor(105);

	for (long long i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	
	calcNumDiv(MAX_N);

	for (int i = 0; i < 100; i++) {
		cout << i << " " << F[i] << endl;
	}


	return 0;
}