#include <string>
#include <sstream>
#include <random>
#include <iostream>
using namespace std;

struct Coord {
	int y_;
	int x_;
	Coord(const int y = 0, const int x = 0) : y_(y), x_(x){}
};

std::mt19937 mt_for_action(0); // �s���I��p�̗����������������


constexpr const int H = 3; // ���H�̍���
constexpr const int W = 4; // ���H�̕�
constexpr int END_TURN = 4; // �Q�[���I���^�[��


// ��l�Q�[���̗�
// 1�^�[���ɏ㉺���E�l�����̂����ꂩ��1�}�X���i�ށB
// ���ɂ���|�C���g�𓥂ނƎ��g�̃X�R�A�ƂȂ�A���̃|�C���g��������B
// END_TURN�̎��_�̃X�R�A���������邱�Ƃ��ړI
class MazeState {
private:
	// �E�A���A���A��ւ̈ړ�������x������y����
	static constexpr const int dx[4] = { 1, -1, 0, 0 };
	static constexpr const int dy[4] = { 0, 0, 1, -1 };

	int points_[H][W] = {}; // ���̃|�C���g��1-9�ŕ\������
	int turn_ = 0; // ���݂̃^�[��

public:
	Coord character_ = Coord();
	int game_score_ = 0; // �Q�[����Ŏ��ۂɓ����X�R�A
	MazeState() {}

	// h * w�̖��H�𐶐�����B
	MazeState(const int seed) {
		auto mt_for_construct = mt19937(seed); // �Ֆʍ\�z�p�̗����������������
		this->character_.y_ = mt_for_construct() % H;
		this->character_.x_ = mt_for_construct() % W;

		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				if (y == character_.y_ && x == character_.x_) {
					continue;
				}
				this->points_[y][x] = mt_for_construct() % 10;
			}
		}

	}

	// [�ǂ̃Q�[���ł���������]�F�Q�[���̏I������
	bool isDone() const {
		return this->turn_ == END_TURN;
	}

	// [�ǂ̃Q�[���ł���������]�F�w�肵��action�ŃQ�[����1�^�[���i�߂�
	void advance(const int action) {
		this->character_.x_ += dx[action];
		this->character_.y_ += dy[action];
		auto& point = this->points_[this->character_.y_][this->character_.x_];
		if (point > 0) {
			this->game_score_ += point;
			point = 0;
		}
		this->turn_++;
	}


	// [�ǂ̃Q�[���ł���������]�F���݂̏󋵂Ńv���C���[���\�ȍs�����ׂĂ��擾����
	vector<int> legalActions() const {
		vector<int> actions;
		for (int action = 0; action < 4; action++) {
			int ty = this->character_.y_ + dy[action];
			int tx = this->character_.x_ + dx[action];
			if (ty >= 0 && ty < H && tx >= 0 && tx < W) {
				actions.emplace_back(action);
			}
		}
		return actions;
	}

	// [�������Ȃ��Ă��ǂ�����������ƕ֗�]�F���݂̃Q�[���󋵂𕶎���ɂ���
	string toString() const {
		stringstream ss;
		ss << "turn:\t" << this->turn_ << endl;
		ss << "score:\t" << this->game_score_ << endl;

		for (int h = 0; h < H; h++) {
			for (int w = 0; w < W; w++) {
				if (this->character_.y_ == h && this->character_.x_ == w) {
					ss << '@';
				}
				else if (this->points_[h][w] > 0) {
					ss << points_[h][w];
				}
				else {
					ss << ".";
				}
			}
			ss << endl;
		}
		return ss.str();
	}


};

using State = MazeState;

// �����_���ɍs�������肷��
int randomAction(const State& state) {
	auto legal_actions = state.legalActions();

	return legal_actions[mt_for_action() % (legal_actions.size())];
}


// �V�[�h���w�肵�ăQ�[���󋵂�\�����Ȃ���AI�Ƀv���C������B
void playGame(const int seed) {
	
	auto state = State(seed);
	cout << state.toString() << endl;

	while (!state.isDone()) {
		state.advance(randomAction(state));
		cout << state.toString() << endl;
	}
}

int main() {

	playGame(/*�Ֆʏ������̃V�[�h*/ 121321);

	return 0;
}