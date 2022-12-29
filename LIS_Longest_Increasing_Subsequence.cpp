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
const int INF = 10000000000;
const long long LINF = 3e18 + 7;
const int MAX_N = 7000010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

// �Œ�������������
// �a�{ p. 63
// ����n�̐��� a0, a1, ..., an ������܂��B���̐���̑���������̂����A�Œ��̂��̂̒��������߂Ȃ����B
// �������A����������Ƃ́A�S�Ă�i<j��ai<aj�𖞂���������������B
// 5
// 4 2 3 1 5

int N;
int a[MAX_N];
int dp[MAX_N];


// dp[i] = �Ōオa[i]�ł���悤�ȍŒ��̑���������̒���
// a[i]�݂̂���Ȃ�� or j < i ���Aaj < ai �ł���悤��aj�ŏI��鑝��������̌���ai��t����������
// �̂ǂ��炩
// �܂�A dp[i] = max{1, dp[j] + 1 | j < i ���� aj < ai }
int solve() {
	int res = 0;
	for (int i = 0; i < N; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (a[j] < a[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		res = max(res, dp[i]);
	}

	return res;
}


// dp[i] = ������ i+1 �ł���悤�ȑ���������ɂ�����ŏI�v�f�̍ŏ��l�i���݂��Ȃ��ꍇ��INF�j
// �ڍׂ͋a�{ p. 65
int fastest_solve() {
	for (int i = 0; i < N; i++) {
		dp[i] = INF;
	}

	for (int i = 0; i < N; i++) {
		*lower_bound(dp, dp + N, a[i]) = a[i];
	}

	return lower_bound(dp, dp + N, INF) - dp;
}

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}

	cout << fastest_solve() << endl;


	return 0;
}