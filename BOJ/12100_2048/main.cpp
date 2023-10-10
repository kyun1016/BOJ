#include<vector>
#include<fstream>
#include<iostream>
#include<string>
#include<cassert>
#include<queue>
#include<memory>

namespace cls_12100 {
	class Board
	{
	public:
		Board(const int& size, const std::vector<std::vector<int>>& array);
		~Board() = default;

		void MoveAll(const int& depth);
		void MoveR();
		void MoveL();
		void MoveU();
		void MoveD();
		int GetMaxValue() const;
	private:
		int mSize;
		std::vector<std::vector<int>> mArray;
		bool mVisit[5][4];
		int mMaxValue;
	};

	Board::Board(const int& size, const std::vector<std::vector<int>>& array)
		: mSize(size)
		, mArray(array)
		, mMaxValue(0)
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				mVisit[i][j] = false;
			}
		}
	}

	void Board::MoveAll(const int& depth)
	{
		if (depth < 5)
		{
			std::vector<std::vector<int>> beforeArray(mArray);
			MoveR();
			MoveAll(depth + 1);
			mArray = beforeArray;
			MoveL();
			MoveAll(depth + 1);
			mArray = beforeArray;
			MoveU();
			MoveAll(depth + 1);
			mArray = beforeArray;
			MoveD();
			MoveAll(depth + 1);
			mArray = beforeArray;
		}
	}

	void Board::MoveR()
	{
		std::queue<int> queue;
		bool mergeFlag = false;
		for (int y = 0; y < mSize; ++y)
		{
			for (int x = mSize - 1; x >= 0; --x)
			{
				if (mArray[y][x] != 0) {
					if (queue.size() == 0) {
						mergeFlag = false;
						queue.push(mArray[y][x]);
					}
					else if (queue.back() == mArray[y][x] && !mergeFlag)
					{
						mergeFlag = true;
						queue.back() += mArray[y][x];
					}
					else
					{
						mergeFlag = false;
						queue.push(mArray[y][x]);
					}
				}
			}
			for (int x = mSize - 1; x >= 0; --x)
			{
				if (!queue.empty())
				{
					mArray[y][x] = queue.front();
					mMaxValue = mMaxValue > mArray[y][x] ? mMaxValue : mArray[y][x];
					queue.pop();
				}
				else
				{
					mArray[y][x] = 0;
				}
			}
		}
	}
	void Board::MoveL()
	{
		std::queue<int> queue;
		bool mergeFlag = false;
		for (int y = 0; y < mSize; ++y)
		{
			for (int x = 0; x < mSize; ++x)
			{
				if (mArray[y][x] != 0) {
					if (queue.size() == 0) {
						mergeFlag = false;
						queue.push(mArray[y][x]);
					}
					else if (queue.back() == mArray[y][x] && !mergeFlag)
					{
						mergeFlag = true;
						queue.back() += mArray[y][x];
					}
					else
					{
						mergeFlag = false;
						queue.push(mArray[y][x]);
					}
				}
			}
			for (int x = 0; x < mSize; ++x)
			{
				if (!queue.empty())
				{
					mArray[y][x] = queue.front();
					mMaxValue = mMaxValue > mArray[y][x] ? mMaxValue : mArray[y][x];
					queue.pop();
				}
				else
				{
					mArray[y][x] = 0;
				}
			}
		}
	}
	void Board::MoveU()
	{
		std::queue<int> queue;
		bool mergeFlag = false;
		for (int x = 0; x < mSize; ++x)
		{
			for (int y = mSize - 1; y >= 0; --y)
			{
				if (mArray[y][x] != 0) {
					if (queue.size() == 0) {
						mergeFlag = false;
						queue.push(mArray[y][x]);
					}
					else if (queue.back() == mArray[y][x] && !mergeFlag)
					{
						mergeFlag = true;
						queue.back() += mArray[y][x];
					}
					else
					{
						mergeFlag = false;
						queue.push(mArray[y][x]);
					}
				}
			}
			for (int y = mSize - 1; y >= 0; --y)
			{
				if (!queue.empty())
				{
					mArray[y][x] = queue.front();
					mMaxValue = mMaxValue > mArray[y][x] ? mMaxValue : mArray[y][x];
					queue.pop();
				}
				else
				{
					mArray[y][x] = 0;
				}
			}
		}
	}
	void Board::MoveD()
	{
		std::queue<int> queue;
		bool mergeFlag = false;
		for (int x = 0; x < mSize; ++x)
		{
			for (int y = 0; y < mSize; ++y)
			{
				if (mArray[y][x] != 0) {
					if (queue.size() == 0) {
						mergeFlag = false;
						queue.push(mArray[y][x]);
					}
					else if (queue.back() == mArray[y][x] && !mergeFlag)
					{
						mergeFlag = true;
						queue.back() += mArray[y][x];
					}
					else
					{
						mergeFlag = false;
						queue.push(mArray[y][x]);
					}
				}
			}
			for (int y = 0; y < mSize; ++y)
			{
				if (!queue.empty())
				{
					mArray[y][x] = queue.front();
					mMaxValue = mMaxValue > mArray[y][x] ? mMaxValue : mArray[y][x];
					queue.pop();
				}
				else
				{
					mArray[y][x] = 0;
				}
			}
		}
	}
	int Board::GetMaxValue() const
	{
		return mMaxValue;
	}
}

void test(const std::string& fileName)
{
	int size, answer;
	std::vector<std::vector<int>> array;

	std::ifstream filePtr("input" + fileName + ".txt");
	std::string temp;
	std::getline(filePtr, temp);
	size = std::stoi(temp);

	array.resize(size, std::vector<int>(size));
	int x = 0;
	int y = 0;
	while (std::getline(filePtr, temp))
	{
		int beforeIndex = 0;
		int curIndex = temp.find(' ');
		for (int x = 0; x < size; ++x)
		{
			array[y][x] = std::stoi(temp.substr(beforeIndex, curIndex));
			beforeIndex = curIndex + 1;
			curIndex = temp.find(' ', beforeIndex);
		}
		++y;
	}

	filePtr.close();

	filePtr.open("output" + fileName + ".txt");
	std::getline(filePtr, temp);
	answer = std::stoi(temp);
	filePtr.close();

	cls_12100::Board* board = new cls_12100::Board(size, array);
	board->MoveAll(0);
	std::cout << board->GetMaxValue() << std::endl;
	delete board;
}

void answer()
{
	int size;
	std::cin >> size;
	std::cin.ignore(100, '\n');

	std::vector<std::vector<int>> array;
	array.resize(size, std::vector<int>(size));

	std::string temp;
	for (int y = 0; y < size; ++y)
	{
		getline(std::cin, temp);
		int beforeIndex = 0;
		int curIndex = temp.find(' ');
		for (int x = 0; x < size; ++x)
		{
			array[y][x] = std::stoi(temp.substr(beforeIndex, curIndex));
			beforeIndex = curIndex + 1;
			curIndex = temp.find(' ', beforeIndex);
		}
	}

	cls_12100::Board* board = new cls_12100::Board(size, array);
	board->MoveAll(0);
	std::cout << board->GetMaxValue() << std::endl;
	delete board;
}

int main()
{
	//test("1");

	answer();

	return 0;
}