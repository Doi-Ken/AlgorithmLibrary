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

constexpr const int H = 6; // 迷路の高さ
constexpr const int W = 7; // 迷路の幅

using ScoreType = int64_t;
constexpr const ScoreType INF = 1000000000LL;

enum WinningStatus
{
	WIN,
	LOSE,
	DRAW,
	NONE,
};

class ConnectFourState {
private:
	static constexpr const int dx[2] = { 1, -1 };          // 移動方向のx成分
	static constexpr const int dy_right_up[2] = { 1, -1 }; // "／"方向のy成分
	static constexpr const int dy_leftt_up[2] = { -1, 1 }; // "\"方向のy成分
	bool is_first_ = true;	// 先手番であるか
	int my_board_[H][W] = {};
	int enemy_board_[H][W] = {};
	WinningStatus winning_status_ = WinningStatus::NONE;

public:
	ConnectFourState(){}

	// [どのゲームでも実装する]：ゲームが終了したか判定する
	bool isDone() const {
		return winning_status_ != WinningStatus::NONE;
	}

	// [どのゲームでも実装する]：指定したactionでゲームを1ターン進め、次のプレイヤー視点の盤面にする
	void advance(const int action) {
		pair<int, int> coordinate;
		for (int y = 0; y < H; y++) {
			if (this->my_board_[y][action] == 0 && this->enemy_board_[y][action] == 0) {
				this->my_board_[y][action] = 1;
				coordinate = pair<int, int>(y, action);
				break;
			}
		}

		{ // 横方向の連結判定
			
			auto que = deque<pair<int, int>>();
			que.emplace_back(coordinate);
			vector<vector<bool>> check(H, vector<bool>(W, false));
			int count = 0;
			while (!que.empty()) {
				const auto& tmp_cod = que.front();
				que.pop_front();
				count++;
				if (count >= 4) {
					this->winning_status_ = WinningStatus::LOSE; // 自分の駒が揃ったら相手視点負け
					break;
				}
				check[tmp_cod.first][tmp_cod.second] = true;
				for (int action = 0; action < 2; action++) {
					int ty = tmp_cod.first;
					int tx = tmp_cod.second + dx[action];
					if (ty >= 0 && ty < H && tx >= 0 && tx < W && my_board_[ty][tx] == 1 && !check[ty][tx]) {
						que.emplace_back(ty, tx);
					}
				}
			}
		}
		if (!isDone()) {
			// "／"方向の連結判定
			auto que = deque<pair<int, int>>();
			que.emplace_back(coordinate);
			vector<vector<bool>> check(H, vector<bool>(W, false));
			int count = 0;
			while (!que.empty()) {
				const auto& tmp_cod = que.front();
				que.pop_front();
				count++;
				if (count >= 4) {
					this->winning_status_ = WinningStatus::LOSE; // 自分の駒が揃ったら相手視点負け
					break;
				}
				check[tmp_cod.first][tmp_cod.second] = true;
				for (int action = 0; action < 2; action++) {
					int ty = tmp_cod.first + dy_right_up[action];
					int tx = tmp_cod.second + dx[action];
					if (ty >= 0 && ty < H && tx >= 0 && tx < W && my_board_[ty][tx] == 1 && !check[ty][tx]) {
						que.emplace_back(ty, tx);
					}
				}
			
				if (!isDone()) {
					// "／"方向の連結判定
					auto que = deque<pair<int, int>>();
					que.emplace_back(coordinate);
					vector<vector<bool>> check(H, vector<bool>(W, false));
					int count = 0;
					while (!que.empty()) {
						const auto& tmp_cod = que.front();
						que.pop_front();
						count++;
						if (count >= 4) {
							this->winning_status_ = WinningStatus::LOSE; // 自分の駒が揃ったら相手視点負け
							break;
						}
						check[tmp_cod.first][tmp_cod.second] = true;
						for (int action = 0; action < 2; action++) {
							int ty = tmp_cod.first + dy_leftt_up[action];
							int tx = tmp_cod.second + dx[action];
							if (ty >= 0 && ty < H && tx >= 0 && tx < W && my_board_[ty][tx] == 1 && !check[ty][tx]) {
								que.emplace_back(ty, tx);
							}
						}
					}
				}
			}
		}
		if (!isDone()) {
			// 縦方向の連結判定
			int ty = coordinate.first;
			int tx = coordinate.second;
			bool is_win = true;
			for (int i = 0; i < 4; i++) {
				bool is_mine = (ty >= 0 && ty < H&& tx >= 0 && tx < W&& my_board_[ty][tx] == 1);
				if (!is_mine) {
					is_win = false;
					break;
				}
				ty--;
			}
			if (is_win) this->winning_status_ = WinningStatus::LOSE;	// 自分の駒がそろったら相手視点負け
		}

		swap(my_board_, enemy_board_);
		is_first_ = !is_first_;
		if (this->winning_status_ == WinningStatus::NONE && legalActions().size() == 0) {
			this->winning_status_ = WinningStatus::DRAW;
		}

	}

	// [どのゲームでも実装する]：勝敗情報を取得する
	WinningStatus getWinningStatus() const {
		return this->winning_status_;
	}

	// [どのゲームでも実装する]：現在のプレイヤーが可能な行動を全て取得する
	vector<int> legalActions() const {
		vector<int> actions;
		for (int x = 0; x < W; x++) {
			for (int y = H - 1; y >= 0; y--) {
				if (my_board_[y][x] == 0 && enemy_board_[y][x] == 0) {
					actions.emplace_back(x);
					break;
				}
			}
		}
		return actions;
	}

	// [実装しなくてもよいが実装すると便利] : 現在のゲーム状況を文字列にする
	std::string toString() const
	{
		std::stringstream ss("");

		ss << "is_first:\t" << this->is_first_ << "\n";
		for (int y = H - 1; y >= 0; y--)
		{
			for (int x = 0; x < W; x++)
			{
				char c = '.';
				if (my_board_[y][x] == 1)
				{
					c = (is_first_ ? 'x' : 'o');
				}
				else if (enemy_board_[y][x] == 1)
				{
					c = (is_first_ ? 'o' : 'x');
				}
				ss << c;
			}
			ss << "\n";
		}

		return ss.str();
	}

};


using State = ConnectFourState;

using AIFunction = std::function<int(const State&)>;
using StringAIPair = std::pair<std::string, AIFunction>;

// ランダムに行動を決定する
int randomAction(const State& state)
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
	// プレイアウト回数を指定して原始モンテカルロ法で行動を決定する
	int primitiveMontecarloAction(const State& state, int playout_number)
	{
		auto legal_actions = state.legalActions();
		auto values = std::vector<double>(legal_actions.size());
		auto cnts = std::vector<double>(legal_actions.size());
		for (int cnt = 0; cnt < playout_number; cnt++)
		{
			int index = cnt % legal_actions.size();

			State next_state = state;
			next_state.advance(legal_actions[index]);
			values[index] += 1. - playout(&next_state);
			++cnts[index];
		}
		int best_action_index = -1;
		double best_score = -INF;
		for (int index = 0; index < legal_actions.size(); index++)
		{
			double value_mean = values[index] / cnts[index];
			if (value_mean > best_score)
			{
				best_score = value_mean;
				best_action_index = index;
			}
		}
		return legal_actions[best_action_index];
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
	};

	// プレイアウト数を指定してMCTSで行動を決定する
	int mctsAction(const State& state, const int playout_number) {

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
		return legal_actions[best_action_index];
	}
}

using montecarlo::mctsAction;
using montecarlo::primitiveMontecarloAction;


using AIFunction = std::function<int(const State&)>;
using StringAIPair = std::pair<std::string, AIFunction>;

// ゲームを1回プレイしてゲーム状況を表示する
void playGame()
{
	using std::cout;
	using std::endl;
	auto state = State();
	cout << state.toString() << endl;
	while (!state.isDone())
	{
		// 1p
		{
			cout << "1p ------------------------------------" << endl;
			int action = randomAction(state);
			cout << "action " << action << endl;
			state.advance(action); // (a-1) ここで視点が入れ替わり、2p視点になる。
			cout << state.toString() << endl;
			if (state.isDone())
			{

				switch (state.getWinningStatus()) // (a-2) a-1で2P視点になっているので、WINなら2pの勝利
				{
				case (WinningStatus::WIN):
					cout << "winner: "
						<< "2p" << endl;
					break;
				case (WinningStatus::LOSE):
					cout << "winner: "
						<< "1p" << endl;
					break;
				default:
					cout << "DRAW" << endl;
					break;
				}
				break;
			}
		}
		// 2p
		{
			cout << "2p ------------------------------------" << endl;
			int action = randomAction(state);
			cout << "action " << action << endl;
			state.advance(action); // (b-1) ここで視点が入れ替わり、1p視点になる。
			cout << state.toString() << endl;
			if (state.isDone())
			{

				switch (state.getWinningStatus()) // (b-2) b-1で2P視点になっているので、WINなら1pの勝利
				{
				case (WinningStatus::WIN):
					cout << "winner: "
						<< "1p" << endl;
					break;
				case (WinningStatus::LOSE):
					cout << "winner: "
						<< "2p" << endl;
					break;
				default:
					cout << "DRAW" << endl;
					break;
				}
				break;
			}
		}
	}
}

int main() {

	playGame();

	return 0;
}