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

// Crossing judge
// �a�{ p. 225
// POJ 1127 http://poj.org/problem?id=1127
// �O�ς̐��� https://www.nekonecode.com/math-lab/pages/vector2/cross2/

double EPS = 1e-10;

// �덷���l�����đ����Z���s��
double add(double a, double b) {
	if (abs(a + b) < EPS * (abs(a) + abs(b))) {
		return 0;
	}
	return a + b;
}

// 2�����x�N�g���\����
struct P {
	double x, y;
	P() {};
	P(double x, double y) : x(x), y(y) {
	}
	P operator + (P p) {
		return P(add(x, p.x), add(y, p.y));
	}
	P operator - (P p) {
		return P(add(x, -p.x), add(y, -p.y));
	}
	P operator * (double d) {
		return P(x * d, y * d);
	}
	double dot(P p) {
		return add(x * p.x, y * p.y);
	}
	double det(P p) {
		return add(x * p.y, -y * p.x);
	}
};

// ����p1-p2��ɓ_q�����邩����
// �O�ς�0�͐^���΂̃x�N�g�� or ���������̃x�N�g��
// ���ς�0�ȉ���q��p1, q��p2�x�N�g����90�x�ȏ�
bool on_seg(P p1, P p2, P q) {
	return (p1 - q).det(p2 - q) == 0 && (p1 - q).dot(p2 - q) <= 0;
}

// ����p1-p1�ƒ���q1-q2�̌�_
// �a�{ p. 226�Q��
P intersection(P p1, P p2, P q1, P q2) {
	return p1 + (p2 - p1) * ((q2 - q1).det(q1 - p1) / (q2 - q1).det(p2 - p1));
}

int N;
P p[100], q[100];
int M;
int a[100], b[100];

bool g[100][100]; // �ڑ��֌W�̃O���t

int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> p[i].x >> p[i].y >> q[i].x >> q[i].y;
	}
	
	int va, vb;
	M = 0;
	while (cin >> va >> vb) {
		if (va == 0 && vb == 0) {
			break;
		}
		a[M] = va - 1;
		b[M] = vb - 1;
		M++;
	}


	for (int i = 0; i < N; i++) {
		g[i][i] = true;
		for (int j = 0; j < i; j++) {
			// �_i�Ɩ_j�����L�_����������
			if ((p[i] - q[i]).det(p[j] - q[j]) == 0) {
				// ���s�ȏꍇ�A�i�ǂꂩ�̓_�������̐�����ɂ���Ηǂ��j
				g[i][j] = g[j][i] = on_seg(p[i], q[i], p[j])
					|| on_seg(p[i], q[i], q[j])
					|| on_seg(p[j], q[j], p[i])
					|| on_seg(p[j], q[j], q[i]);
			}
			else {
				// ���s�łȂ��ꍇ�A(��_�����邩)
				P r = intersection(p[i], q[i], p[j], q[j]);
				g[i][j] = g[j][i] = on_seg(p[i], q[i], r) && on_seg(p[j], q[j], r); // ����pq �ii��j�j��r�͌���邩
			}
		}
	}

	// ���[�V�����t���C�h�@�őS�_�Ԃ̘A�����������
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				g[i][j] |= g[i][k] && g[k][j];
			}
		}
	}

	for (int i = 0; i < M; i++) {
		if (g[a[i]][b[i]]) {
			cout << "CONNECTED" << endl;
		}
		else {
			cout << "NOT CONNECTED" << endl;
		}
	}


	return 0;
}