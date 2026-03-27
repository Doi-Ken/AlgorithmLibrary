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
#include <random>
#include <chrono>
#include <array>
#include <unordered_set>
#include <bitset>
using namespace std;
const long long LINF = 3e18 + 7;
const int MAX_N = 5000010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//const int INF = 2147483647;
//using ll = long long;


int operator_count = 0;


class State {
public:
	int value_;
	State(const int value = 0) : value_(value) {}
	void operator=(const State& state) {
		this->value_ = state.value_;
		operator_count++;
	}
};

bool operator<(const State& state1, const State& state2) {
	return state1.value_ < state2.value_;
}

int main() {

	std::mt19937 mt(0);
	priority_queue<State> queue;
	for (int i = 0; i < 100; i++) {
		queue.push(State(mt() % 100));
	}
	cout << "operator is called " << operator_count << " times" << endl;



	return 0;
}