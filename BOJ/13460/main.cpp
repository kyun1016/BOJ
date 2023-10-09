#include<vector>
#include<fstream>
#include<iostream>
#include<string>
#include<cassert>
#include<queue>

namespace ans {
	class Board
	{
	public:
		Board(const int& height, const int& width, const std::vector<std::vector<char>>& array);
		~Board() = default;

		int CalcBestWay();
		void Move();
		void MoveR();
		void MoveL();
		void MoveU();
		void MoveD();
		void Reset();
	private:
		int mWidth;
		int mHeight;
		std::vector<std::vector<bool>> mArray;
		int mPosCurRed[2];
		int mPosCurBlue[2];
		int mPosStartRed[2];
		int mPosStartBlue[2];
		int mPosGoal[2];
		int mCache[10][10][10][10];
		int mBestCnt;
		std::queue<std::pair<std::pair<int, int>, std::pair<int, int>>> mQueue;
	};

	Board::Board(const int& height, const int& width, const std::vector<std::vector<char>>& array)
		: mHeight(height)
		, mWidth(width)
		, mBestCnt(-1)
	{
		mArray.resize(mHeight, std::vector<bool>(mWidth));

		for (int y = 0; y < mHeight; ++y)
		{
			for (int x = 0; x < mWidth; ++x)
			{
				for (int y2 = 0; y2 < mHeight; ++y2)
					for (int x2 = 0; x2 < mWidth; ++x2)
						mCache[y][x][y2][x2] = -1;
				if (array[y][x] == '#')
				{
					mArray[y][x] = false;
					continue;
				}
				else if (array[y][x] == 'R')
				{
					mPosCurRed[1] = y;
					mPosCurRed[0] = x;
					mPosStartRed[1] = y;
					mPosStartRed[0] = x;
				}
				else if (array[y][x] == 'B')
				{
					mPosCurBlue[1] = y;
					mPosCurBlue[0] = x;
					mPosStartBlue[1] = y;
					mPosStartBlue[0] = x;
				}
				else if (array[y][x] == 'O')
				{
					mPosGoal[1] = y;
					mPosGoal[0] = x;
				}
				mArray[y][x] = true;
			}
		}
		mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] = 0;
		mQueue.push({ {mPosCurRed[1], mPosCurRed[0]}, {mPosCurBlue[1], mPosCurBlue[0]} });
	}
	int Board::CalcBestWay()
	{
		Move();
		return mBestCnt;
	}
	void Board::Move()
	{
		int posRed[2];
		int posBlue[2];

		while (!mQueue.empty()) {
			posRed[1] = mQueue.front().first.first;
			posRed[0] = mQueue.front().first.second;
			posBlue[1] = mQueue.front().second.first;
			posBlue[0] = mQueue.front().second.second;
			mQueue.pop();

			mPosCurRed[1] = posRed[1];
			mPosCurRed[0] = posRed[0];
			mPosCurBlue[1] = posBlue[1];
			mPosCurBlue[0] = posBlue[0];
			MoveR();
			mPosCurRed[1] = posRed[1];
			mPosCurRed[0] = posRed[0];
			mPosCurBlue[1] = posBlue[1];
			mPosCurBlue[0] = posBlue[0];
			MoveL();
			mPosCurRed[1] = posRed[1];
			mPosCurRed[0] = posRed[0];
			mPosCurBlue[1] = posBlue[1];
			mPosCurBlue[0] = posBlue[0];
			MoveU();
			mPosCurRed[1] = posRed[1];
			mPosCurRed[0] = posRed[0];
			mPosCurBlue[1] = posBlue[1];
			mPosCurBlue[0] = posBlue[0];
			MoveD();
			if (mBestCnt != -1)
				return;
		}
	}
	
	void Board::MoveR()
	{
		int moveCount = mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]];
		bool posFlag = mPosCurRed[0] < mPosCurBlue[0]; // [. . R B] or [. . B R]
		bool redFall = false;
		bool blueFall = false;

		for (int x = mPosCurRed[0] + 1; x < mWidth; ++x)
		{
			if (mArray[mPosCurRed[1]][x])
				mPosCurRed[0] = x;
			else
				break;
			if (mPosGoal[1] == mPosCurRed[1] && mPosGoal[0] == mPosCurRed[0])
				redFall = true;
		}
		for (int x = mPosCurBlue[0] + 1; x < mWidth; ++x)
		{
			if (mArray[mPosCurBlue[1]][x])
				mPosCurBlue[0] = x;
			else
				break;
			if (mPosGoal[1] == mPosCurBlue[1] && mPosGoal[0] == mPosCurBlue[0])
				blueFall = true;
		}

		if (mPosCurRed[0] == mPosCurBlue[0] && mPosCurRed[1] == mPosCurBlue[1])
		{
			if (posFlag)
				--mPosCurRed[0];
			else
				--mPosCurBlue[0];
		}

		if (redFall && !blueFall)
		{
			mBestCnt = moveCount + 1;
		}

		if ((mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] == -1 || mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] > moveCount + 1) && !redFall && !blueFall)
		{
			mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] = moveCount + 1;
			mQueue.push({ {mPosCurRed[1], mPosCurRed[0]}, {mPosCurBlue[1], mPosCurBlue[0]} });
		}
	}
	void Board::MoveL()
	{
		int moveCount = mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]];
		bool posFlag = mPosCurRed[0] < mPosCurBlue[0]; // [. . R B] or [. . B R]
		bool redFall = false;
		bool blueFall = false;

		for (int x = mPosCurRed[0] - 1; x > 0; --x)
		{
			if (mArray[mPosCurRed[1]][x])
				mPosCurRed[0] = x;
			else
				break;
			if (mPosGoal[1] == mPosCurRed[1] && mPosGoal[0] == mPosCurRed[0])
				redFall = true;
		}
		for (int x = mPosCurBlue[0] - 1; x > 0; --x)
		{
			if (mArray[mPosCurBlue[1]][x])
				mPosCurBlue[0] = x;
			else
				break;
			if (mPosGoal[1] == mPosCurBlue[1] && mPosGoal[0] == mPosCurBlue[0])
				blueFall = true;
		}

		if (mPosCurRed[0] == mPosCurBlue[0] && mPosCurRed[1] == mPosCurBlue[1])
		{
			if (posFlag)
				++mPosCurBlue[0];
			else
				++mPosCurRed[0];
		}

		if (redFall && !blueFall)
		{
			mBestCnt = moveCount + 1;
		}

		if ((mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] == -1 || mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] > moveCount + 1) && !redFall && !blueFall)
		{
			mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] = moveCount + 1;
			mQueue.push({ {mPosCurRed[1], mPosCurRed[0]}, {mPosCurBlue[1], mPosCurBlue[0]} });
		}
	}

	void Board::MoveU()
	{
		int moveCount = mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]];
		bool posFlag = mPosCurRed[1] < mPosCurBlue[1]; // [. . R B] or [. . B R]
		bool redFall = false;
		bool blueFall = false;

		for (int y = mPosCurRed[1] + 1; y < mHeight; ++y)
		{
			if (mArray[y][mPosCurRed[0]])
				mPosCurRed[1] = y;
			else
				break;
			if (mPosGoal[1] == mPosCurRed[1] && mPosGoal[0] == mPosCurRed[0])
				redFall = true;
		}
		for (int y = mPosCurBlue[1] + 1; y < mHeight; ++y)
		{
			if (mArray[y][mPosCurBlue[0]])
				mPosCurBlue[1] = y;
			else
				break;
			if (mPosGoal[1] == mPosCurBlue[1] && mPosGoal[0] == mPosCurBlue[0])
				blueFall = true;
		}

		if (mPosCurRed[0] == mPosCurBlue[0] && mPosCurRed[1] == mPosCurBlue[1])
		{
			if (posFlag)
				--mPosCurRed[1];
			else
				--mPosCurBlue[1];
		}

		if (redFall && !blueFall)
		{
			mBestCnt = moveCount + 1;
		}

		if ((mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] == -1 || mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] > moveCount + 1) && !redFall && !blueFall)
		{
			mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] = moveCount + 1;
			mQueue.push({ {mPosCurRed[1], mPosCurRed[0]}, {mPosCurBlue[1], mPosCurBlue[0]} });
		}
	}
	void Board::MoveD()
	{
		int moveCount = mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]];
		bool posFlag = mPosCurRed[1] < mPosCurBlue[1]; // [. . R B] or [. . B R]
		bool redFall = false;
		bool blueFall = false;

		for (int y = mPosCurRed[1] - 1; y > 0; --y)
		{
			if (mArray[y][mPosCurRed[0]])
				mPosCurRed[1] = y;
			else
				break;
			if (mPosGoal[1] == mPosCurRed[1] && mPosGoal[0] == mPosCurRed[0])
				redFall = true;
		}
		for (int y = mPosCurBlue[1] - 1; y > 0; --y)
		{
			if (mArray[y][mPosCurBlue[0]])
				mPosCurBlue[1] = y;
			else
				break;
			if (mPosGoal[1] == mPosCurBlue[1] && mPosGoal[0] == mPosCurBlue[0])
				blueFall = true;
		}

		if (mPosCurRed[0] == mPosCurBlue[0] && mPosCurRed[1] == mPosCurBlue[1])
		{
			if (posFlag)
				++mPosCurBlue[1];
			else
				++mPosCurRed[1];
		}

		if (redFall && !blueFall)
		{
			mBestCnt = moveCount + 1;
		}

		if ((mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] == -1 || mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] > moveCount + 1) && !redFall && !blueFall)
		{
			mCache[mPosCurRed[1]][mPosCurRed[0]][mPosCurBlue[1]][mPosCurBlue[0]] = moveCount + 1;
			mQueue.push({ {mPosCurRed[1], mPosCurRed[0]}, {mPosCurBlue[1], mPosCurBlue[0]} });
		}
	}
	void Board::Reset()
	{
		mPosCurBlue[1] = mPosStartBlue[1];
		mPosCurBlue[0] = mPosStartBlue[0];
		mPosCurRed[1] = mPosStartRed[1];
		mPosCurRed[0] = mPosStartRed[0];
	}
}

void test(const std::string& fileName)
{
	int height, width, answer;
	std::vector<std::vector<char>> array;
	
	std::ifstream filePtr("input" + fileName + ".txt");
	std::string temp;
	std::getline(filePtr, temp, ' ');
	height = std::stoi(temp);

	std::getline(filePtr, temp);
	width = std::stoi(temp);

	array.resize(height, std::vector<char>(width));
	int y = 0;
	while (std::getline(filePtr, temp))
	{
		for (int x = 0; x < width; ++x)
		{
			array[y][x] = temp[x];
		}
		++y;
	}
	filePtr.close();

	filePtr.open("output" + fileName + ".txt");
	std::getline(filePtr, temp);
	answer = std::stoi(temp);
	filePtr.close();

	ans::Board* board = new ans::Board(height, width, array);
	std::cout << board->CalcBestWay() << std::endl;
	//assert(answer == board->CalcBestWay());
	delete board;
}

void answer()
{
	int height, width;
	std::cin >> height >> width;

	std::vector<std::vector<char>> array;
	array.resize(height, std::vector<char>(width));

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			std::cin >> array[y][x];
		}
	}

	ans::Board* board = new ans::Board(height, width, array);
	std::cout << board->CalcBestWay() << std::endl;
	delete board;
}

int main()
{
	//test("1");
	//test("2");
	//test("3");
	//test("4");
	//test("5");
	//test("6");
	//test("7");
	
	answer();

	return 0;
}

