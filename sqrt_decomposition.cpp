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
const int MAX_N = 2000010;
const int MAX_W = 10002;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// p. 168 sqrt decomposition
// POJ 2104

const int B = 1000;

int N, M;
long long A[MAX_N];
int I[MAX_N], J[MAX_N], K[MAX_N];
long long nums[MAX_N];
vector<long long> bucket[MAX_N / B];

int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < M; i++) {
		cin >> I[i] >> J[i] >> K[i];
		I[i]--;
		J[i]--;
	}

	for (int i = 0; i < N; i++) {
		bucket[i / B].push_back(A[i]);
		nums[i] = A[i];
	}

	sort(nums, nums + N);

	for (int i = 0; i < N / B; i++) {
		sort(bucket[i].begin(), bucket[i].end());
	}


	for (int i = 0; i < M; i++) {
		int l = I[i];
		int r = J[i] + 1;
		int k = K[i];

		int ub = N - 1;
		int lb = -1;

		while (ub - lb > 1) {
			int mid = (ub + lb) / 2;
			long long x = nums[mid];
			int tl = l;
			int tr = r;
			int c = 0;

			while (tl < tr && tl % B != 0) {
				if (A[tl] <= x) {
					c++;
				}
				tl++;
			}

			while (tl < tr && tr % B != 0) {
				tr--;
				if (A[tr] <= x) {
					c++;
				}
			}

			while (tl < tr) {
				int b = tl / B;
				c += upper_bound(bucket[b].begin(), bucket[b].end(), x) - bucket[b].begin();
				tl += B;
			}
			
			if (c >= k) {
				ub = mid;
			}
			else {
				lb = mid;
			}
		}

		cout << nums[ub] << endl;
	}

	return 0;
}