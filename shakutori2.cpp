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

long long N;
long long S;
long long a[MAX_N];

int main() {

	
	cin >> N;
	cin >> S;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}

	long long res = 0;
	long long ans = N;
	long long left = 0;
	long long right = 0;
	long long sum = 0;

	while (left < N) {

		while (right < N && sum < S) {
			sum += a[right];
			right++;
		}

		if (sum < S) {
			break;
		}

		res = right - left;
		ans = min(ans, res);

		sum -= a[left];
		left++;
	}


	if (ans > N) {
		ans = 0;
	}
	cout << ans << endl;


	return 0;
}