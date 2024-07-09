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

// TDPC T - フィボナッチ
// https://atcoder.jp/contests/tdpc/tasks/tdpc_fibonacci

// https://drken1215.hatenablog.com/entry/2023/05/02/160300 (これをURL等を飛ばしながら普通に読む)
// 上記「3.提出コード」の前に以下を読む
// https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a (これは「Bostan–Mori のアルゴリズム」～「フィボナッチ数とリュカ数」の手前までを読む)
// と理解できると思う
// https://trap.jp/post/1657/ （これは参考）

long long mod_pow(long long x, long long n, long long mod) {
	long long res = 1;
	while (n > 0) {
		if (n & 1) {
			res = ((res * x) % mod);
		}
		x = ((x * x) % mod);
		n >>= 1;
	}

	return res;
}

long long K, N;

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

const int mod = 1000000007;

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

vector<ll> naive_mul(const vector<ll>& A, const vector<ll>& B) {
	if (A.empty() || B.empty()) return {};
	int n = (int)A.size(), m = (int)B.size();
	vector<ll> res(n + m - 1);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			res[i + j] += A[i] * B[j];
			res[i + j] %= mod;
		}
	return res;
}


ll bostan_mori(vector<ll>& P, vector<ll>& Q, long long N) {
	if (N == 0) {
		return P[0] * mod_pow(Q[0], Q[0] - 2, mod) % mod; // P[0] / Q[0];
	}

	long long qdeg = Q.size();

	vector<ll> tP2{ P };
	vector<ll> minusQ{ Q };

	tP2.resize(qdeg - 1);


	for (int i = 1; i < Q.size(); i += 2) {
		minusQ[i] = (mod - minusQ[i]) % mod;
	}

	vector<ll> P2 = naive_mul(tP2, minusQ);

	vector<ll> tQ2{ Q };

	vector<ll> Q2 = naive_mul(tQ2, minusQ);



	vector<ll> S(qdeg - 1), T(qdeg);
	for (int i = 0; i < S.size(); i++) {
		S[i] = (N % 2 == 0 ? P2[i * 2] : P2[i * 2 + 1]);
	}

	for (int i = 0; i < T.size(); i++) {
		T[i] = Q2[i * 2];
	}



	return bostan_mori(S, T, N >> 1);

}


int main() {

	cin >> K >> N;

	vector<ll> P(K), Q(K + 1);

	Q[0] = 1;
	for (int i = 0; i < P.size(); i++) {
		P[i] = (1LL + mod - i) % mod;
	}
	for (int i = 1; i < Q.size(); i++) {
		Q[i] = (mod - 1) % mod;
	}


	cout << bostan_mori(P, Q, N - 1) << endl;

	return 0;
}