#include <string>
#include <sstream>
#include <random>
#include <iostream>
#include <queue>
#include <chrono>
#include <functional>
using namespace std;

std::mt19937 mt_for_action(0); // �s���I��p�̗����������������
constexpr const int H = 5; // ���H�̍���
constexpr const int W = 5; // ���H�̕�
constexpr int END_TURN = 5; // �Q�[���I���^�[��
constexpr int CHARACER_N = 3; // �L�����N�^�[�̐�

using ScoreType = int64_t;     // �Q�[���̕]���X�R�A�̌^�����߂Ă����B
constexpr const ScoreType INF = 1000000000LL; // ���蓾�Ȃ����炢�傫�ȃX�R�A�̗��p�ӂ��Ă���


struct Coord {
	int y_;
	int x_;
	Coord(const int y = 0, const int x = 0) : y_(y), x_(x) {}
};



// ������l�Q�[���̗�
// �L�����N�^�[��1�}�X��̍ł��|�C���g���������Ɏ����ňړ�����B
// ���@��̒��ŃX�R�A�����l�̂��̂�����ꍇ�A�E�A���A���A��̏��ōs�����D�悳���B
// 1�^�[���ɏ㉺���E�l�����̂����ꂩ�ɕǂ̂Ȃ��ꏊ��1�}�X���i�ށB
// ���ɂ���|�C���g�𓥂ނƎ��g�̃X�R�A�ƂȂ�A���̃|�C���g��������B
// END_TURN�̎��_�̃X�R�A���������邱�Ƃ�ړI�Ƃ��A
// �Q�[���ɉ���ł���v�f�Ƃ��āA������Ԃł̃L�����N�^�[���ǂ��ɔz�u���邩��I���ł���B
// �ǂ̂悤�ɃL�����N�^�[��z�u����ƍŏI�X�R�A�������Ȃ邩���l����Q�[���B
class AutoMoveMazeState
{
private:
	static constexpr const int dx[4] = { 1, -1, 0, 0 };
	static constexpr const int dy[4] = { 0, 0, 1, -1 };

	int points_[H][W] = {}; // ���̃|�C���g��1-9�ŕ\������
	int turn_; // ���݂̃^�[��
	Coord characters_[CHARACER_N] = {}; // CHARACTER_N�̂̃L�����N�^�[

	// �w��L�����N�^�[���ړ�������B
	void movePlayer(const int character_id) {
		Coord& character = this->characters_[character_id];
		int best_point = -INF;
		int best_action_index = 0;
		for (int action = 0; action < 4; action++) {
			int ty = character.y_ + dy[action];
			int tx = character.x_ + dx[action];
			if (ty >= 0 && ty < H && tx >= 0 && tx < W) {
				auto point = this->points_[ty][tx];
				if (point > best_point) {
					best_point = point;
					best_action_index = action;
				}
			}
		}

		character.y_ += dy[best_action_index];
		character.x_ += dx[best_action_index];
	}

	// �Q�[����1�^�[���i�߂�B
	void advance() {

		for (int character_id = 0; character_id < CHARACER_N; character_id++) {
			movePlayer(character_id);
		}
		for (auto& character : this->characters_) {
			auto& point = this->points_[character.y_][character.x_];
			this->game_score_ += point;
			point = 0;
		}
		++this->turn_;
	}


public:
	int game_score_; // �Q�[����Ŏ��ۂɓ����X�R�A
	ScoreType evaluated_score_; // �T����ŕ]�������X�R�A

	// h * w �̖��H�𐶐�����B
	AutoMoveMazeState(const int seed) : turn_(0),
		game_score_(0),
		evaluated_score_(0) {

		auto mt_for_construct = std::mt19937(seed);
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				points_[y][x] = mt_for_construct() % 9 + 1;
			}
		}
	}

	// �w��ʒu�Ɏw��L�����N�^�[��z�u����B
	void setCharacter(const int character_id, const int y, const int x) {
		this->characters_[character_id].y_ = y;
		this->characters_[character_id].x_ = x;
	}


	
	// [�ǂ̃Q�[���ł���������]�F�Q�[���̏I������
	bool isDone() const {
		return this->turn_ == END_TURN;
	}

	// [�������Ȃ��Ă��悢����������ƕ֗�] : ���݂̃Q�[���󋵂𕶎���ɂ���
	std::string toString() const
	{
		std::stringstream ss;
		ss << "turn:\t" << this->turn_ << "\n";
		ss << "score:\t" << this->game_score_ << "\n";
		auto board_chars = std::vector<std::vector<char>>(H, std::vector<char>(W, '.'));
		for (int h = 0; h < H; h++)
		{
			for (int w = 0; w < W; w++)
			{
				bool is_written = false; // ���̍��W�ɏ������������肵����

				for (const auto& character : this->characters_)
				{
					if (character.y_ == h && character.x_ == w)
					{
						ss << "@";
						is_written = true;
						break;
					}
					board_chars[character.y_][character.x_] = '@';
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

	// [�ǂ̃Q�[���ł���������] :
	// �X�R�A�v�Z����B
	// (toString���������Ȃ��ꍇ�͈���is_print�ƈ��̕t�����鏈���͕s�v
	ScoreType getScore(bool is_print = false) const
	{
		auto tmp_state = *this;
		// �L�����N�^�[�̈ʒu�ɂ���|�C���g������
		for (auto& character : this->characters_) {
			auto& point = tmp_state.points_[character.y_][character.x_];
			point = 0;
		}
		// �I������܂ŃL�����N�^�[�̈ړ����J��Ԃ��B
		while (!tmp_state.isDone()) {
			tmp_state.advance();
			if (is_print)
				cout << tmp_state.toString() << endl;
		}
		return tmp_state.game_score_;
	}

	// [�ǂ̃Q�[���ł���������] : ����������
	void init() {
		for (auto& character : this->characters_) {
			character.y_ = mt_for_action() % H;
			character.x_ = mt_for_action() % W;
		}
	}

	// [�ǂ̃Q�[���ł���������] : ��ԑJ�ڂ���
	void transition() {
		auto& character = this->characters_[mt_for_action() % CHARACER_N];
		character.y_ = mt_for_action() % H;
		character.x_ = mt_for_action() % W;
	}
};

using State = AutoMoveMazeState;

State hillClimb(const State& state, int number) {

	State now_state = state;
	now_state.init();
	ScoreType best_score = now_state.getScore();

	for (int i = 0; i < number; i++) {
		auto next_state = now_state;
		next_state.transition();
		auto next_score = next_state.getScore();
		if (next_score > best_score) {
			best_score = next_score;
			now_state = next_state;
		}
	}

	return now_state;
}

using AIFunction = function<State(const State&)>;
using StringAIPair = pair<string, AIFunction>;

// �Q�[����1��v���C���ăQ�[��������\������
void playGame(const StringAIPair& ai, const int seed) {
	auto state = State(seed);
	state = ai.second(state);
	cout << state.toString() << endl;
	auto score = state.getScore(true);
	cout << "Score of " << ai.first << ": " << score << endl;

}

int main() {

	const auto& ai = StringAIPair("hillClimb", [&](const State& state)
		{ return hillClimb(state, 10000); });
	playGame(ai, 0); // �Ֆʐ����V�[�h��0�ɐݒ肵�ăv���C����B

	return 0;
}