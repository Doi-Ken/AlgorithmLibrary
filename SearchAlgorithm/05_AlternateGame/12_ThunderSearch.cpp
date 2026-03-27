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

enum WinningStatus
{
	WIN,
	LOSE,
	DRAW,
	NONE,
};

constexpr const int H = 10; // 迷路の高さ
constexpr const int W = 10; // 迷路の幅
constexpr int END_TURN = 50; // ゲーム終了ターン

using ScoreType = int64_t;
constexpr const ScoreType INF = 1000000000LL;

class AlternateMazeState {
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

	// 現在のプレイヤーが先手であるか判定する
	bool isFirstPlayer() const {
		return this->turn_ % 2 == 0;
	}
public:
	// [実装しなくてもよいが実装すると便利]
	// 先手のプレイヤーの勝率計算のためのスコアを計算する
	double getFirstPlayerScoreForWinRate() const {
		switch (this->getWinningStatus()) {
		case (WinningStatus::WIN):
			if (this->isFirstPlayer()) return 1.;
			else return 0.;
		case (WinningStatus::LOSE):
			if (this->isFirstPlayer()) return 0.;
			else return 1.;
		default:
			return 0.5;
		}

	}

	AlternateMazeState(const int seed) : points_(H, vector<int>(W)),
		turn_(0),
		characters_({
		Character(H / 2, (W / 2) - 1),
		Character(H / 2, (W / 2) + 1) }) {
		auto mt_for_construct = std::mt19937(seed);

		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				int point = mt_for_construct() % 10;
				if (characters_[0].y_ == y && characters_[0].x_ == x) continue;
				if (characters_[1].y_ == y && characters_[1].x_ == x) continue;
				this->points_[y][x] = point;
			}
		}
	}

	// [どのゲームでも実装する]：ゲームが終了したか判定する
	bool isDone() const {
		return this->turn_ == END_TURN;
	}

	// [どのゲームでも実装する]：
	// 指定したactionでゲームを1ターン進め、次のプレイヤー視点の盤面にする
	void advance(const int action) {
		auto& character = this->characters_[0];
		character.x_ += dx[action];
		character.y_ += dy[action];
		auto& point = this->points_[character.y_][character.x_];
		if (point > 0) {
			character.game_score_ += point;
			point = 0;
		}
		this->turn_++;
		swap(this->characters_[0], this->characters_[1]);
	}

	// [どのゲームでも実装する]：現在のプレイヤーが可能な行動を全て取得する
	vector<int> legalActions() const {
		vector<int> actions;
		const auto& character = this->characters_[0];
		for (int action = 0; action < 4; action++) {
			int ty = character.y_ + dy[action];
			int tx = character.x_ + dx[action];
			if (ty >= 0 && ty < H && tx >= 0 && tx < W) {
				actions.emplace_back(action);
			}
		}
		return actions;
	}

	// [どのゲームでも実装する]：勝敗情報を取得する
	WinningStatus getWinningStatus() const
	{
		if (isDone())
		{
			if (characters_[0].game_score_ > characters_[1].game_score_)
				return WinningStatus::WIN;
			else if (characters_[0].game_score_ < characters_[1].game_score_)
				return WinningStatus::LOSE;
			else
				return WinningStatus::DRAW;
		}
		else {
			return WinningStatus::NONE;
		}
	}

	// [どのゲームでも実装する]：現在のプレイヤー視点の盤面評価をする
	ScoreType getScore() const {
		return characters_[0].game_score_ - characters_[1].game_score_;
	}

	// [どのゲームでも実装する]：現在のプレイヤー視点の盤面評価し、0~1の値を返す
	double getScoreRate() const {
		if (characters_[0].game_score_ + characters_[1].game_score_ == 0)
			return 0;
		return ((double)characters_[0].game_score_) / (double)(characters_[0].game_score_ + characters_[1].game_score_);
	}

	// [実装しなくてもよいが実装すると便利]：現在のゲーム状況を文字列にする
	string toString() const {
		stringstream ss("");
		ss << "turn:\t" << this->turn_ << "\n";
		for (int player_id = 0; player_id < this->characters_.size(); player_id++) {
			int actual_player_id = player_id;
			if (this->turn_ % 2 == 1) {
				// 奇数ターンの場合は初期配置の視点で見るとplayer_idが逆
				actual_player_id = (player_id + 1) % 2;
			}
			const auto& chara = this->characters_[actual_player_id];
			ss << "score(" << player_id << "):\t" << chara.game_score_;
			ss << "\ty: " << chara.y_ << " x: " << chara.x_ << "\n";
		}

		for (int h = 0; h < H; h++) {
			for (int w = 0; w < W; w++) {
				bool is_written = false; // この座標に各文字が決定したか
				for (int player_id = 0; player_id < characters_.size(); player_id++) {
					int actual_player_id = player_id;
					if (this->turn_ % 2 == 1) {
						actual_player_id = (player_id + 1) % 2;
					}
					const auto& character = this->characters_[player_id];
					if (character.y_ == h && character.x_ == w) {
						if (actual_player_id == 0) {
							ss << 'A';
						}
						else {
							ss << 'B';
						}
						is_written = true;
					}
				}
				if (!is_written) {
					if (this->points_[h][w] > 0) {
						ss << points_[h][w];
					}
					else {
						ss << '.';
					}
				}
			}
			ss << '\n';
		}
		return ss.str();
	}

};

using State = AlternateMazeState;


// ランダムに行動を決定する
int randomAction(const State &state)
{
    auto legal_actions = state.legalActions();
    return legal_actions[mt_for_action() % (legal_actions.size())];
}


namespace montecarlo {

	// ランダムプレイアウトをして勝敗スコアを計算する
	double playout(State* state)
	{ // const&にすると再帰中にディープコピーが必要になるため、高速化のためポインタにする。(constでない参照でも可)
		switch (state->getWinningStatus())
		{
		case (WinningStatus::WIN):
			return 1.;
		case (WinningStatus::LOSE):
			return 0.;
		case (WinningStatus::DRAW):
			return 0.5;
		default:
			state->advance(randomAction(*state));
			return 1. - playout(state);
		}
	}

	constexpr const double C = 1.; // UCB1の計算に使う定数
	constexpr const int EXPAND_THRESHOLD = 10; // ノードを展開する閾値
	
	// MCTSの計算に使うノード
	class Node {
	private:
		State state_;
		double w_; // 累計価値
	public:
		vector<Node> child_nodes_;
		double n_; // 試行回数

		Node(const State& state) : state_(state), w_(0), n_(0) {}

		// ノードの評価を行う
		double evaluate() {
			// ゲーム終了時
			if (this->state_.isDone()) {
				double value = 0.5;
				switch (this->state_.getWinningStatus()) {
				case(WinningStatus::WIN):
					value = 1;
					break;
				case(WinningStatus::LOSE):
					value = 0;
					break;
				default:
					break;
				}
				this->w_ += value;
				this->n_++;
				return value;
			}
			// 子ノードが存在しないとき
			if (this->child_nodes_.empty()) {
				State state_copy = this->state_;
				double value = playout(&state_copy);
				this->w_ += value;
				this->n_++;
				if (this->n_ == EXPAND_THRESHOLD) this->expand();
				return value;
			}
			// 子ノードが存在するとき
			else {
				double value = 1. - this->nextChildNode().evaluate();
				this->w_ += value;
				this->n_++;
				return value;
			}
		}

		// ノードを展開する
		void expand() {
			auto legal_actions = this->state_.legalActions();
			this->child_nodes_.clear();
			for (const auto action : legal_actions) {
				this->child_nodes_.emplace_back(this->state_);
				this->child_nodes_.back().state_.advance(action);
			}
		}

		// どのノードを評価するか選択する
		Node& nextChildNode() {
			for (auto& child_node : this->child_nodes_) {
				if (child_node.n_ == 0) return child_node;
			}
			double t = 0;
			for (const auto& child_node : this->child_nodes_) t += child_node.n_;
			double best_value = -INF;
			int best_action_index = -1;
			for (int i = 0; i < this->child_nodes_.size(); i++) {
				const auto& child_node = this->child_nodes_[i];
				double ucb1_value =
					1. - child_node.w_ / child_node.n_
					+ (double)C * sqrt(2. * log(t) / child_node.n_); // 子ノードの価値の平均 を、親ノードの手番プレイヤー視点に直すため 1-w/n
				if (ucb1_value > best_value) {
					best_action_index = i;
					best_value = ucb1_value;
				}
			}
			return this->child_nodes_[best_action_index];
		}

		void printTree(const int depth = 1) const {

			for (int i = 0; i < child_nodes_.size(); i++) {
				const auto& child_node = child_nodes_[i];
				for (int j = 0; j < depth; j++) cout << "__";
				cout << " " << i << "(" << child_node.n_ << ")" << endl;
				if (!child_node.child_nodes_.empty()) child_node.printTree(depth + 1);
			}
		}
	};

	// プレイアウト数を指定してMCTSで行動を決定する
	int mctsAction(const State& state, const int playout_number, const bool is_print) {

		Node root_node = Node(state);
		root_node.expand();
		for (int i = 0; i < playout_number; i++) {
			root_node.evaluate();
		}
		auto legal_actions = state.legalActions();
		int best_action_searched_number = -1;
		int best_action_index = -1;
		assert(legal_actions.size() == root_node.child_nodes_.size());
		for (int i = 0; i < legal_actions.size(); i++) {
			int n = root_node.child_nodes_[i].n_;
			if (n > best_action_searched_number) {
				best_action_index = i;
				best_action_searched_number = n;
			}
		}
		{
			static bool called_cnt = false;
			if (is_print && !called_cnt) {
				// プリントしたい
				cout << __func__ << endl;
				root_node.printTree();
			}
			called_cnt = true;
		}

		return legal_actions[best_action_index];
	}
}

namespace thunder {

	// ランダムプレイアウトをして勝敗スコアを計算する
	double playout(State* state)
	{ // const&にすると再帰中にディープコピーが必要になるため、高速化のためポインタにする。(constでない参照でも可)
		switch (state->getWinningStatus())
		{
		case (WinningStatus::WIN):
			return 1.;
		case (WinningStatus::LOSE):
			return 0.;
		case (WinningStatus::DRAW):
			return 0.5;
		default:
			state->advance(randomAction(*state));
			return 1. - playout(state);
		}
	}

	constexpr const double C = 1.; // UCB1の計算に使う定数
	constexpr const int EXPAND_THRESHOLD = 10; // ノードを展開する閾値

	// MCTSの計算に使うノード
	class Node {
	private:
		State state_;
		double w_; // 累計価値
	public:
		vector<Node> child_nodes_;
		double n_; // 試行回数

		Node(const State& state) : state_(state), w_(0), n_(0) {}

		// ノードの評価を行う
		double evaluate() {
			// ゲーム終了時
			if (this->state_.isDone()) {
				double value = 0.5;
				switch (this->state_.getWinningStatus()) {
				case(WinningStatus::WIN):
					value = 1;
					break;
				case(WinningStatus::LOSE):
					value = 0;
					break;
				default:
					break;
				}
				this->w_ += value;
				this->n_++;
				return value;
			}
			// 子ノードが存在しないとき
			if (this->child_nodes_.empty()) {
				double value = this->state_.getScoreRate();
				this->w_ += value;
				this->n_++;
				this->expand();
				return value;
			}
			// 子ノードが存在するとき
			else {
				double value = 1. - this->nextChildNode().evaluate();
				this->w_ += value;
				this->n_++;
				return value;
			}
		}

		// ノードを展開する
		void expand() {
			auto legal_actions = this->state_.legalActions();
			this->child_nodes_.clear();
			for (const auto action : legal_actions) {
				this->child_nodes_.emplace_back(this->state_);
				this->child_nodes_.back().state_.advance(action);
			}
		}

		// どのノードを評価するか選択する
		Node& nextChildNode() {
			for (auto& child_node : this->child_nodes_) {
				if (child_node.n_ == 0) return child_node;
			}
			double t = 0;
			for (const auto& child_node : this->child_nodes_) t += child_node.n_;
			double best_value = -INF;
			int best_action_index = -1;
			for (int i = 0; i < this->child_nodes_.size(); i++) {
				const auto& child_node = this->child_nodes_[i];
				double ucb1_value =
					1. - child_node.w_ / child_node.n_; // 子ノードの価値の平均 を、親ノードの手番プレイヤー視点に直すため 1-w/n
				if (ucb1_value > best_value) {
					best_action_index = i;
					best_value = ucb1_value;
				}
			}
			return this->child_nodes_[best_action_index];
		}

		void printTree(const int depth = 1) const {

			for (int i = 0; i < child_nodes_.size(); i++) {
				const auto& child_node = child_nodes_[i];
				for (int j = 0; j < depth; j++) cout << "__";
				cout << " " << i << "(" << child_node.n_ << ")" << endl;
				if (!child_node.child_nodes_.empty()) child_node.printTree(depth + 1);
			}
		}
	};

	// プレイアウト数を指定してMCTSで行動を決定する
	int thunderSearchAction(const State& state, const int playout_number, const bool is_print) {

		Node root_node = Node(state);
		root_node.expand();
		for (int i = 0; i < playout_number; i++) {
			root_node.evaluate();
		}
		auto legal_actions = state.legalActions();
		int best_action_searched_number = -1;
		int best_action_index = -1;
		assert(legal_actions.size() == root_node.child_nodes_.size());
		for (int i = 0; i < legal_actions.size(); i++) {
			int n = root_node.child_nodes_[i].n_;
			if (n > best_action_searched_number) {
				best_action_index = i;
				best_action_searched_number = n;
			}
		}
		{
			static bool called_cnt = false;
			if (is_print && !called_cnt) {
				// プリントしたい
				cout << __func__ << endl;
				root_node.printTree();
			}
			called_cnt = true;
		}

		return legal_actions[best_action_index];
	}
}

using montecarlo::mctsAction;
using thunder::thunderSearchAction;


using AIFunction = std::function<int(const State&)>;
using StringAIPair = std::pair<std::string, AIFunction>;
// ゲームをgame_number×2(先手後手を交代)回プレイしてaisの0番目のAIの勝率を表示する。
void testFirstPlayerWinRate(const std::array<StringAIPair, 2>& ais, const int game_number)
{
	using std::cout;
	using std::endl;

	double first_player_win_rate = 0;
	for (int i = 0; i < game_number; i++)
	{
		auto base_state = State(i);
		for (int j = 0; j < 2; j++)
		{ // 先手後手平等に行う
			auto state = base_state;
			auto& first_ai = ais[j];
			auto& second_ai = ais[(j + 1) % 2];
			while (true)
			{
				state.advance(first_ai.second(state));
				if (state.isDone())
					break;
				state.advance(second_ai.second(state));
				if (state.isDone())
					break;
			}
			double win_rate_point = state.getFirstPlayerScoreForWinRate();
			if (j == 1)
				win_rate_point = 1 - win_rate_point;
			if (win_rate_point >= 0)
			{
				state.toString();
			}
			first_player_win_rate += win_rate_point;
		}
		cout << "i " << i << " w " << first_player_win_rate / ((i + 1) * 2) << endl;
	}
	first_player_win_rate /= (double)(game_number * 2);
	cout << "Winning rate of " << ais[0].first << " to " << ais[1].first << ":\t" << first_player_win_rate << endl;
}

int main() {

	auto ais = array<StringAIPair, 2>{
		StringAIPair("thunderSearchAction 300", [](const State& state)
			{ return thunder::thunderSearchAction(state, 300, false); }),
			StringAIPair("mctsAction 300", [](const State& state)
				{return montecarlo::mctsAction(state, 300, false); })
	};

	testFirstPlayerWinRate(ais, 100);

	return 0;
}