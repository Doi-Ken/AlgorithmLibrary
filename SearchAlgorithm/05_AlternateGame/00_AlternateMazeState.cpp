#include <string>
#include <sstream>
#include <random>
#include <iostream>
#include <queue>
#include <chrono>
#include <functional>
using namespace std;

std::mt19937 mt_for_action(0);

constexpr const int H = 3;  // ���H�̍���
constexpr const int W = 3;  // ���H�̕�
constexpr int END_TURN = 4; // �Q�[���I���^�[��

struct Character
{
	int y_;
	int x_;
	int game_score_;
	Character(const int y = 0, const int x = 0) : y_(y), x_(x), game_score_(0) {}
};


enum WinningStatus
{
	WIN,
	LOSE,
	DRAW,
	NONE,
};

class AlternateMazeState
{
private:
	static constexpr const int dx[4] = { 1, -1, 0, 0 };
	static constexpr const int dy[4] = { 0, 0, 1, -1 };

	vector<vector<int>> points_; // ���̃|�C���g��1-9�ŕ\������
	int turn_; // ���݂̃^�[��
	vector<Character> characters_;

public:
	AlternateMazeState(const int seed) : points_(H, vector<int>(W)),
		turn_(0),
		characters_({ Character(H / 2, (W / 2) - 1), Character(H / 2, (W / 2) + 1) })
	{
		auto mt_for_construct = mt19937(seed);

		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				int point = mt_for_construct() % 10;
				if (characters_[0].y_ == y && characters_[0].x_ == x) {
					continue;
				}
				if (characters_[1].y_ == y && characters_[1].x_ == x) {
					continue;
				}
				this->points_[y][x] = point;
			}
		}
	}

	// [�ǂ̃Q�[���ł���������] : �Q�[�����I�����������肷��
	bool isDone() const
	{
		return this->turn_ == END_TURN;
	}

	// [�ǂ̃Q�[���ł���������] :
	// �w�肵��action�ŃQ�[����1�^�[���i�߁A���̃v���C���[���_�̔Ֆʂɂ���
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

	// [�ǂ̃Q�[���ł���������] : ���݂̃v���C���[���\�ȍs�������ׂĎ擾����
	vector<int> legalActions() const
	{
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

	// [�ǂ̃`�[���ł���������] : ���s�����擾����
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

	// [�������Ȃ��Ă��ǂ�����������ƕ֗�] : ���݂̃Q�[���󋵂𕶎���ɂ���
	string toString() const
	{
		stringstream ss("");
		ss << "turn:\t" << this->turn_ << "\n";
		for (int player_id = 0; player_id < this->characters_.size(); player_id++) {
			int actual_player_id = player_id;
			if (this->turn_ % 2 == 1) {
				actual_player_id = (player_id + 1) % 2; // ��^�[���̏ꍇ�͏����z�u�̎��_�Ō����player_id���t
			}
			const auto& chara = this->characters_[actual_player_id];
			ss << "score(" << player_id << "):\t" << chara.game_score_ << "\ty: " << chara.y_ << " x: " << chara.x_ << "\n";
		}
		for (int h = 0; h < H; h++)
		{
			for (int w = 0; w < W; w++)
			{
				bool is_written = false; // ���̍��W�ɏ������������肵����
				for (int player_id = 0; player_id < this->characters_.size(); player_id++)
				{
					int actual_player_id = player_id;
					if (this->turn_ % 2 == 1)
					{
						actual_player_id = (player_id + 1) % 2; // ��^�[���̏ꍇ�͏����z�u�̎��_�Ō����player_id���t
					}

					const auto& character = this->characters_[player_id];
					if (character.y_ == h && character.x_ == w)
					{
						if (actual_player_id == 0)
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

using State = AlternateMazeState;

// �����_���ɍs�������肷��
int randomAction(const State& state) {
	auto legal_actions = state.legalActions();
	return legal_actions[mt_for_action() % (legal_actions.size())];
}

// �Q�[����1��v���C���ăQ�[���󋵂�\������
void playGame(const int seed) {

	auto state = State(seed);
	cout << state.toString() << endl;
	while (!state.isDone()) {

		// 1p
		{
			cout << "1p ------------------------------------" << endl;
			int action = randomAction(state);
			cout << "action " << action << endl;
			state.advance(action); // (a-1) �����Ŏ��_������ւ��A2p���_�ɂȂ�B
			cout << state.toString() << endl;
			if (state.isDone()) {

				switch (state.getWinningStatus()) // (a-2) a-1��2p���_�ɂȂ��Ă���̂ŁAWIN�Ȃ�2p�̏���
				{
				case(WinningStatus::WIN):
					cout << "winner: "
						<< "2p" << endl;
					break;
				case(WinningStatus::LOSE):
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
			state.advance(action); // (b-1) �����Ŏ��_������ւ��A1p���_�ɂȂ�B
			cout << state.toString() << endl;
			if (state.isDone())
			{

				switch (state.getWinningStatus()) // (b-2) b-1��2P���_�ɂȂ��Ă���̂ŁAWIN�Ȃ�1p�̏���
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

	playGame(4121859904);

	return 0;
}