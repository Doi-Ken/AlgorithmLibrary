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
const int INF = 1000000000;
const long long LINF = 3e18 + 7;
const int MAX_N = 500010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//using ll = long long;

string S;

vector<pair<char, int>> runLengthEncoding(string s) {
    int n = s.length();

    vector<pair<char, int>> res;
    char pre = s[0];
    int cnt = 1;
    for (int i = 1; i < n; i++) {
        if (pre != s[i]) {
            res.push_back({ pre, cnt });
            pre = s[i];
            cnt = 1;
        }
        else cnt++;
    }

    res.push_back({ pre, cnt });
    return res;
}

int main() {

    cin >> S;
    vector<pair<char, int> > rle = runLengthEncoding(S);

    for (int i = 0; i < rle.size(); i++) {
        cout << rle[i].first << " " << rle[i].second << endl;
    }
	
	return 0;
}