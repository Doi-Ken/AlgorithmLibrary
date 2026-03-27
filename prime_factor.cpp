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



// prime factor
map<long long, long long> prime_factor(long long n) {
	map<long long, long long> res;
	for (long long i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			res[i]++;
			n /= i;
		}
	}
	if (n != 1) {
		res[n] = 1;
	}

	return res;
}


int main() {

	long long N;
	cin >> N;

	map<long long, long long> m = prime_factor(N);

	map<long long, long long>::iterator iter = m.begin();
	for (; iter != m.end(); iter++) {
		cout << iter->first << " " << iter->second << endl;
	}

	return 0;
}