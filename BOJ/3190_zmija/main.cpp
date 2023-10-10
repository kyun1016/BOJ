#include<vector>
#include<fstream>
#include<iostream>
#include<string>
#include<cassert>
#include<queue>
#include<memory>

namespace cls_3190 {
	enum eDir{
		R = 0,
		L = 1,
		U = 2,
		D = 3
	};
	class Board
	{
	public:
		Board(const int& size, const std::vector<std::pair<int, int>>& arrayApple, const std::queue<std::pair<int, eDir>>& arraySnake);
		~Board() = default;

		void MoveAll(const int& depth);
		void MoveR();
		void MoveL();
		void MoveU();
		void MoveD();
		int GetMaxValue() const;
	private:
		int mSize;
		std::pair<int, int> mCurPos;
		eDir mCurDir;
		std::unique_ptr<std::unique_ptr<bool[]>[]> mApple;
		std::unique_ptr<std::unique_ptr<bool[]>[]> mSnake;
		std::queue<std::pair<int, eDir>> mMoveQueue;
	};

	Board::Board(const int& size, const std::vector<std::pair<int, int>>& arrayApple, const std::queue<std::pair<int, eDir>>& arraySnake)
		: mSize(size)
		, mCurPos({ 0,0 })
		, mCurDir(R)
		, mApple(std::make_unique<std::unique_ptr<bool[]>[]>(size))
		, mSnake(std::make_unique<std::unique_ptr<bool[]>[]>(size))
		, mMoveQueue(arraySnake)
	{
		for (int i = 0; i < mSize; ++i)
		{
			mApple[i] = std::make_unique<bool[]>(mSize);
			mSnake[i] = std::make_unique<bool[]>(mSize);
		}

		for (size_t i = 0; i < arrayApple.size(); ++i)
		{
			mApple[arrayApple[i].first][arrayApple[i].second] = true;
		}
		mSnake[0][0] = true;
	}
}

void test(const std::string& fileName)
{
}

void answer()
{
	int size, num, numLine;
	std::cin >> size;

	std::vector<std::pair<int,int>> arrayApple;
	std::cin >> num;
	arrayApple.resize(num, std::pair<int, int>({ 0,0 }));
	for (int i = 0; i < num; ++i)
	{
		std::cin >> arrayApple[i].first >> arrayApple[i].second;
		--arrayApple[i].first;
		--arrayApple[i].second;
	}

	std::queue<std::pair<int, cls_3190::eDir>> arraySnake;
	std::cin >> num;
	char temp;
	std::pair<int, cls_3190::eDir> data;
	for (int i = 0; i < num; ++i)
	{
		std::cin >> data.first >> temp;
		if (temp == 'L')
			data.second = cls_3190::L;
		else
			data.second = cls_3190::D;
		arraySnake.push(data);
	}

	cls_3190::Board* board = new cls_3190::Board(size, arrayApple, arraySnake);
	/*board->MoveAll(0);
	std::cout << board->GetMaxValue() << std::endl;*/
	delete board;
}

int main()
{
	//test("1");

	answer();

	return 0;
}