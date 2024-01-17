#include <string>
#include <sstream>
#include <random>
#include <iostream>
#include <queue>
#include <chrono>
using namespace std;

struct Coord {
	int y_;
	int x_;
	Coord(const int y = 0, const int x = 0) : y_(y), x_(x) {}
};


class TimeKeeper {
private:
	chrono::high_resolution_clock::time_point start_time_;
	int64_t time_threshold_;

public:
	// ���Ԑ������~���b�P�ʂŎw�肵�ăC���X�^���X������B
	TimeKeeper(const int64_t& time_threshold) : start_time_(chrono::high_resolution_clock::now()), time_threshold_(time_threshold) {
	}

	// �C���X�^���X��������������w�肵�����Ԑ����𒴉߂��������肷��B
	bool isTimeOver() const {
		using std::chrono::duration_cast;
		using std::chrono::milliseconds;
		auto diff = std::chrono::high_resolution_clock::now() - this->start_time_;

		return duration_cast<milliseconds>(diff).count() >= time_threshold_;
	}


};

std::mt19937 mt_for_action(0); // �s���I��p�̗����������������
using ScoreType = int64_t;     // �Q�[���̕]���X�R�A�̌^�����߂Ă����B
constexpr const ScoreType INF = 1000000000LL; // ���蓾�Ȃ����炢�傫�ȃX�R�A�̗��p�ӂ��Ă���


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
	ScoreType evaluated_score_ = 0; // �T����ŕ]�������X�R�A
	int first_action_ = -1; // �T���؂̃��[�g�m�[�h�ōŏ��ɑI�������s��
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

	// [�ǂ̃Q�[���ł���������]�F�T���p�̔Ֆʕ]��������
	void evaluateScore() {

		this->evaluated_score_ = this->game_score_; // �ȒP�̂��߁A�܂��̓Q�[���X�R�A�����̂܂ܔՖʂ̕]���Ƃ���
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

// [�ǂ̃Q�[���ł���������]�F�T�����̃\�[�g�p�ɕ]�����r����
bool operator<(const MazeState& maze_1, const MazeState& maze_2) {
	return maze_1.evaluated_score_ < maze_2.evaluated_score_;
}


using State = MazeState;

// �r�[��1�{������̃r�[���̕��Ɛ[���A�{�����w�肵��chokudai�T�[�`�ōs�������肷��
int chokudaiSearchAction(const State& state, const int beam_width, const int beam_depth, const int beam_number) {
	
	auto beam = vector<priority_queue<State> >(beam_depth + 1);
	for (int t = 0; t < beam_depth + 1; t++) {
		beam[t] = priority_queue<State>();
	}

	beam[0].push(state);
	for (int cnt = 0; cnt < beam_number; cnt++) {

		for (int t = 0; t < beam_depth; t++) {
			auto& now_beam = beam[t];
			auto& next_beam = beam[t + 1];
			for (int i = 0; i < beam_width; i++) {
				if (now_beam.empty()) {
					break;
				}
				State now_state = now_beam.top();

				if (now_state.isDone()) {
					break;
				}
				now_beam.pop();
				auto legal_actions = now_state.legalActions();
				
				for (const auto& action : legal_actions) {
					State next_state = now_state;
					next_state.advance(action);
					next_state.evaluateScore();
					if (t == 0) {
						next_state.first_action_ = action;
					}
					next_beam.push(next_state);
				}
			}
		}
	}

	for (int t = beam_depth; t >= 0; t--) {
		const auto& now_beam = beam[t];
		if (!now_beam.empty()) {
			return now_beam.top().first_action_;
		}
	}
	return -1;
}

// �Q�[����game_number��v���C���ĕ��σX�R�A��\������
void testAiScore(const int game_number) {

	std::mt19937 mt_for_construct(0);
	double score_mean = 0;
	for (int i = 0; i < game_number; i++) {
		auto state = State(mt_for_construct());

		while (!state.isDone()) {
			state.advance(chokudaiSearchAction(state, /*�r�[����*/ 1, /*�r�[���̐[��*/ END_TURN, /*�r�[����ł�*/ 2));

		}
		auto score = state.game_score_;
		score_mean += score;
	}

	score_mean /= (double)game_number;
	cout << "Score:\t" << score_mean << endl;
}

int main() {

	testAiScore(/*�Q�[�����J��Ԃ���*/ 100);

	return 0;
}