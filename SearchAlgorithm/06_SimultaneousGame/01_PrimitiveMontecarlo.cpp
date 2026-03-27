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

enum WinningStatus {
	FIRST, // プレイヤー0が勝った
	SECOND, // プレイヤー1が勝った
	DRAW,
	NONE,
};

constexpr const int H = 5; // 迷路の高さ
constexpr const int W = 5; // 迷路の幅
constexpr int END_TURN = 20; // ゲーム終了ターン

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

	// [実装しなくてもよいが実装すると便利] : プレイヤー0の勝率計算のためのスコアを計算する
	double getFirstPlayerScoreForWinRate() const
	{
		switch (this->getWinningStatus())
		{
		case (WinningStatus::FIRST):
			return 1.;
		case (WinningStatus::SECOND):
			return 0.;
		default:
			return 0.5;
		}
	}

	// [どのゲームでも実装する]：勝敗情報を取得する
	WinningStatus getWinningStatus() const {
		if (isDone()) {
			if (characters_[0].game_score_ > characters_[1].game_score_)
				return WinningStatus::FIRST;
			else if (characters_[0].game_score_ < characters_[1].game_score_)
				return WinningStatus::SECOND;
			else
				return WinningStatus::DRAW;
		}
		else {
			return WinningStatus::NONE;
		}
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


namespace montecarlo {
	// プレイヤー0視点での評価
	double playout(State* state) {
		// const&にすると再帰中にディープコピーが必要になるため、
		// 高速化のためポインタにする。（const出ない参照でも可）
		switch (state->getWinningStatus()) {
		case (WinningStatus::FIRST):
			return 1.;
		case (WinningStatus::SECOND):
			return 0.;
		case (WinningStatus::DRAW):
			return 0.5;
		default:
			state->advance(randomAction(*state, 0), randomAction(*state, 1));
			return playout(state);
		}
	}

	// プレイアウト数を指定して原始モンテカルロ法で指定したプレイヤーの行動を決定する
	int primitiveMontecarloAction(
		const State& state,
		const int player_id,
		const int playout_number
	) {
		auto my_legal_actions = state.legalActions(player_id);
		auto opp_legal_actions = state.legalActions((player_id + 1) % 2);
		double best_value = -INF;
		int best_action_index = -1;
		for (int i = 0; i < my_legal_actions.size(); i++) {
			double value = 0;
			for (int j = 0; j < playout_number; j++) {
				State next_state = state;
				if (player_id == 0) {
					next_state.advance(
						my_legal_actions[i],
						opp_legal_actions[mt_for_action() % opp_legal_actions.size()]
					);
				}
				else {
					next_state.advance(
						opp_legal_actions[mt_for_action() % opp_legal_actions.size()],
						my_legal_actions[i]
					);
				}
				double player0_win_rate = playout(&next_state);
				double win_rate =
					(player_id == 0 ? player0_win_rate : 1. - player0_win_rate);
				value += win_rate;
			}
			if (value > best_value) {
				best_action_index = i;
				best_value = value;
			}

		}
		return my_legal_actions[best_action_index];
	}
}


using montecarlo::primitiveMontecarloAction;


using AIFunction = std::function<int(const State&, const int)>;
using StringAIPair = std::pair<std::string, AIFunction>;

// ゲームをgame_number回プレイしてaisの0番目のAIの勝率を表示する。
void testFirstPlayerWinRate(std::array<StringAIPair, 2>& ais, const int game_number)
{
	using std::cout;
	using std::endl;
	std::mt19937 mt_for_construct(0);

	double first_player_win_rate = 0;
	for (int i = 0; i < game_number; i++)
	{
		auto state = State(mt_for_construct());
		auto& first_ai = ais[0];
		auto& second_ai = ais[1];
		while (true)
		{
			state.advance(first_ai.second(state, 0), second_ai.second(state, 1));
			if (state.isDone())
				break;
		}
		double win_rate_point = state.getFirstPlayerScoreForWinRate();
		if (win_rate_point >= 0)
		{
			state.toString();
		}
		first_player_win_rate += win_rate_point;

		cout << "i " << i << " w " << first_player_win_rate / (i + 1) << endl;
	}
	first_player_win_rate /= (double)game_number;
	cout << "Winning rate of " << ais[0].first << " to " << ais[1].first << ":\t" << first_player_win_rate << endl;
}

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

		StringAIPair("primitiveMontecarloAction", [](const State& state, const int player_id)
			{ return primitiveMontecarloAction(state, player_id, 1000); }),
			StringAIPair("randomAction", [](const State& state, const int player_id)
				{ return randomAction(state, player_id); }),
	};

	testFirstPlayerWinRate(ais, 500);

	return 0;
}