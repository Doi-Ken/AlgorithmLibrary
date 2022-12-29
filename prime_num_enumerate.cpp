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


long long prime[MAX_N];
bool is_prime[MAX_N];

long long sieve(long long n) {
	long long p = 0;
	for (long long i = 0; i <= n; i++) {
		is_prime[i] = true;
	}
	is_prime[0] = is_prime[1] = false;
	for (long long i = 2; i <= n; i++) {
		if (is_prime[i]) {
			prime[p++] = i;
			for (long long j = 2 * i; j <= n; j += i) {
				is_prime[j] = false;
			}
		}
	}

	return p;
}

int main() {

	long long N = sieve(100);
	cout << N << endl;
	for (long long i = 0; i < N; i++) {
		cout << prime[i] << " ";
	}
	cout << endl;


	return 0;
}