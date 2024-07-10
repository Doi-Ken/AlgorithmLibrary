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
#include <unordered_set>
using namespace std;
const int INF = 1000000007;
const long long LINF = 1e18 + 7;
const int MAX_N = 1200010;
const int MAX_W = 600010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long; 

// linear_equation_gauss_jordan
// http://www.yamamo10.jp/yamamoto/lecture/2006/5E/Linear_eauations/LinearEquations_html/node4.html#google_vignette
// https://atcoder.jp/contests/jag2013summer-day4/tasks/icpc2013summer_day4_f
// https://drken1215.hatenablog.com/entry/2019/03/20/192300

long long N;
long long a[310][310];
typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

const int mod = 2;

mat mul(mat& A, mat& B) {
	mat C(A.size(), vec(B[0].size()));
	for (int i = 0; i < A.size(); i++) {
		for (int k = 0; k < B.size(); k++) {
			for (int j = 0; j < B[0].size(); j++) {
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
			}
		}
	}

	return C;
}


mat pow(mat A, ll n) {
	mat B(A.size(), vec(A.size()));
	for (int i = 0; i < A.size(); i++) {
		B[i][i] = 1;
	}
	while (n > 0) {
		if (n & 1) {
			B = mul(B, A);
		}
		A = mul(A, A);
		n >>= 1;
	}

	return B;
}

long long GaussJordan(mat& A, bool is_extended = false) {
	int rank = 0;
	for (int col = 0; col < A[0].size(); ++col) {
		if (is_extended && col == A[0].size() - 1) break;
		int pivot = -1;
		for (int row = rank; row < A.size(); ++row) {
			if (A[row][col]) {
				pivot = row;
				break;
			}
		}
		if (pivot == -1) continue;
		swap(A[pivot], A[rank]);
		for (int row = 0; row < A.size(); ++row) {
			if (row != rank && A[row][col]) {
				for (int c = 0; c < A[0].size(); c++) {
					A[row][c] ^= A[rank][c];
				}
			}
		}
		++rank;
	}
	return rank;
}


long long linear_equation(mat A, vector<ll> b, vector<ll>& res) {
	int m = A.size(), n = A[0].size();
	mat M(m, vec(n + 1));
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) M[i][j] = A[i][j];
		M[i][n] = b[i];
	}
	int rank = GaussJordan(M, true);

	// check if it has no solution
	for (int row = rank; row < m; ++row) if (M[row][n]) return -1;

	// answer
	res.assign(n, 0);
	for (int i = 0; i < rank; ++i) res[i] = M[i][n];
	return rank;
}



bool has_bit(int n, int i) {
	return (n & (1 << i));
}


int main() {

	cin >> N;

	mat A(N, vec(N));

	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> a[i][j];
			A[i][j] = a[i][j];
		}
	}


	vector<ll> v(N), res;
	for (int i = 0; i < N; i++) {
		cin >> v[i];
	}
	ll T;
	cin >> T;

	mat P = pow(A, T);

	long long rank = linear_equation(P, v, res);
	long long jiyudo = N - rank;

	if (rank == -1) puts("none");
	else if (jiyudo > 0) puts("ambiguous");
	else {
		for (int i = 0; i < N; ++i) {
			cout << res[i];
			if (i != N - 1) cout << " ";
		}
		cout << endl;
	}

	return 0;
}