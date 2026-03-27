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


int a[MAX_W];

void permutation(int n) {

	do {
		for (int i = 0; i < n; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
	} while (next_permutation(a, a + n));

}

bool used[100];
int perm[100];

void permutation1(int pos, int N) {
	if (pos == N) {
		for (int i = 0; i < N; i++) {
			cout << perm[i] << " ";
		}
		cout << endl;
		return;
	}

	for (int i = 0; i < N; i++) {
		if (!used[i]) {
			perm[pos] = i;
			used[i] = true;
			permutation1(pos + 1, N);
			used[i] = false;
		}
	}


}

int main() {

	int n = 5;

	for (int i = 0; i < n; i++) {
		a[i] = i;
	}

	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "------------------" << endl;

	permutation(n);

	cout << "------------------" << endl;
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	
	return 0;
}