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
using namespace std;
const long long LINF = 3e18 + 7;
const int MAX_N = 5000010;
const int MAX_W = 1000010;
const int MAX_ARRAYK = 100000;
double PI = 3.14159265358979323846;
//const int INF = 2147483647;
//using ll = long long;

std::mt19937 mt_for_action(0);


// 時間を管理するクラス
class TimeKeeper
{
private:
	std::chrono::high_resolution_clock::time_point start_time_;
	int64_t time_threshold_;

public:
	// 時間制限をミリ秒単位で指定してインスタンスをつくる。
	TimeKeeper(const int64_t& time_threshold)
		: start_time_(std::chrono::high_resolution_clock::now()),
		time_threshold_(time_threshold)
	{
	}

	// インスタンス生成した時から指定した時間制限を超過したか判定する。
	bool isTimeOver() const
	{
		auto diff = std::chrono::high_resolution_clock::now() - this->start_time_;
		return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() >= time_threshold_;
	}
};

constexpr const int H = 3; // 迷路の高さ
constexpr const int W = 3; // 迷路の幅
constexpr int END_TURN = 4; // ゲーム終了ターン

using ScoreType = int64_t;
constexpr const ScoreType INF = 1000000000LL;
static const std::string dstr[4] = { "RIGHT", "LEFT", "DOWN", "UP" };

class SimultaneousMazeState {
private:
	static constexpr const int dx[4] = { 1, -1, 0, 0 };
	static constexpr const int dy[4] = { 0, 0, 1, -1 };
	struct Character {
		int y_;
		int x_;
		int game_score_;
		Character(const int y = 0, const int x = 0) : y_(y), x_(x), game_score_(0) {};
	};
	vector<vector<int>> points_; // 床のポイントを1~9で表現する
	int turn_;
	vector<Character> characters_;

public:

	SimultaneousMazeState(const int seed) : points_(H, vector<int>(W)),
		turn_(0),
		characters_({
		Character(H / 2, (W / 2) - 1),
		Character(H / 2, (W / 2) + 1)
			}) {
		
		auto mt_for_construct = std::mt19937(seed);

		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W / 2 + 1; x++) {
				int ty = y;
				int tx = x;
				int point = mt_for_construct() % 10;
				if (characters_[0].y_ == y && characters_[0].x_ == x) continue;
				if (characters_[1].y_ == y && characters_[1].x_ == x) continue;
				this->points_[ty][tx] = point;
				tx = W - 1 - x;
				this->points_[ty][tx] = point;
			}
		}
	}
	// [どのゲームでも実装する] : ゲームが終了したか判定する
	bool isDone() const
	{
		return this->turn_ == END_TURN;
	}

	// [どのゲームでも実装する]：指定したactionでゲームを1ターン進める
	void advance(const int action0, const int action1) {
		{
			auto& character = this->characters_[0];
			const auto& action = action0;
			character.x_ += dx[action];
			character.y_ += dy[action];
			const auto point = this->points_[character.y_][character.x_];
			if (point > 0) character.game_score_ += point;
		}
		{
			auto& character = this->characters_[1];
			const auto& action = action1;
			character.x_ += dx[action];
			character.y_ += dy[action];
			const auto point = this->points_[character.y_][character.x_];
			if (point > 0) character.game_score_ += point;
		}

		for (const auto& character : this->characters_) {
			this->points_[character.y_][character.x_] = 0;
		}
		this->turn_++;
	}

	// [どのゲームでも実装する]：指定したプレイヤーが可能な行動を全て取得する
	vector<int> legalActions(const int player_id) const {
		vector<int> actions;
		const auto& character = this->characters_[player_id];
		for (int action = 0; action < 4; action++) {
			int ty = character.y_ + dy[action];
			int tx = character.x_ + dx[action];
			if (ty >= 0 && ty < H && tx >= 0 && tx < W) {
				actions.emplace_back(action);
			}
		}
		return actions;
	}

	// [実装しなくてもよいが実装すると便利] : 現在のゲーム状況を文字列にする
	std::string toString() const
	{
		std::stringstream ss("");
		ss << "turn:\t" << this->turn_ << "\n";
		for (int player_id = 0; player_id < this->characters_.size(); player_id++)
		{
			ss << "score(" << player_id << "):\t" << this->characters_[player_id].game_score_ << "\n";
		}
		for (int h = 0; h < H; h++)
		{
			for (int w = 0; w < W; w++)
			{
				bool is_written = false; // この座標に書く文字が決定したか
				for (int player_id = 0; player_id < this->characters_.size(); player_id++)
				{
					const auto& character = this->characters_[player_id];
					if (character.y_ == h && character.x_ == w)
					{
						if (player_id == 0)
						{
							ss << 'A';
						}
						else
						{
							ss << 'B';
						}
						is_written = true;
					}
				}
				if (!is_written)
				{
					if (this->points_[h][w] > 0)
					{
						ss << points_[h][w];
					}
					else
					{
						ss << '.';
					}
				}
			}
			ss << '\n';
		}

		return ss.str();
	}

};

using State = SimultaneousMazeState;

// 指定したプレイヤーの行動をランダムに決定する
int randomAction(const State& state, const int player_id) {
	auto legal_actions = state.legalActions(player_id);
	return legal_actions[mt_for_action() % (legal_actions.size())];
}


using AIFunction = std::function<int(const State&, const int)>;
using StringAIPair = std::pair<std::string, AIFunction>;

void playGame(const array<StringAIPair, 2>& ais, const int seed) {
	auto state = State(seed);
	cout << state.toString() << endl;

	while (!state.isDone()) {
		vector<int> actions = { ais[0].second(state, 0), ais[1].second(state, 1) };
		cout << "actions " << dstr[actions[0]] << " " << dstr[actions[1]] << endl;
		state.advance(actions[0], actions[1]);
		cout << state.toString() << endl;
	}
}


int main() {

	auto ais = std::array<StringAIPair, 2>{

		StringAIPair("randomAction", [](const State& state, const int player_id)
			{ return randomAction(state, player_id); }),
			StringAIPair("randomAction", [](const State& state, const int player_id)
				{ return randomAction(state, player_id); }),
	};

	playGame(ais, /*盤面初期化のシード*/ 0);


	return 0;
}