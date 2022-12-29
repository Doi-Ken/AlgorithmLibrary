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
int a[MAX_N];
int K;


// reference 
// https://qiita.com/ganyariya/items/33f1326154b85db465c3
// 
// lower_bound
int binary_search_lower_bound() {
	int lb = -1;
	int ub = N;

	while (ub - lb > 1) {
		int mid = (lb + ub) / 2;
		if (a[mid] >= K) {
			ub = mid;
		}
		else {
			lb = mid;
		}
	}

	return ub;
}

// upper_bound
int binary_search_upper_bound() {
	int lb = -1;
	int ub = N;

	while (ub - lb > 1) {
		int mid = (lb + ub) / 2;
		if (a[mid] > K) {
			ub = mid;
		}
		else {
			lb = mid;
		}
	}

	return ub;
}


int main() {

	// sample
	//5
	//2 3 3 5 6
	//3

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}
	cin >> K;

	// lower_boundは、探索したいkey以上のイテレータを返す
    // upper_boundは、探索したいkeyより大きいイテレータを返す
	cout << binary_search_lower_bound() << endl;
	cout << lower_bound(a, a + N, K) - a << endl;

	cout << binary_search_upper_bound() << endl;	
	cout << upper_bound(a, a + N, K) - a << endl;


	return 0;
}