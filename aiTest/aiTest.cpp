// aiTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include <vector>
#include <Windows.h>

using namespace std;

mt19937 seed;

int random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(seed);
}

struct myPOINT
{
	int x, y;

	myPOINT()
		:x(0), y(0)
	{
	}

	myPOINT(int x, int y)
		:x(x), y(y)
	{
	}
};

int GetIdx(int x, int y)
{
	return y * 10 + x;
}

int GetIdx(const myPOINT& pt)
{
	return pt.y * 10 + pt.x;
}

myPOINT GetPt(int idx)
{
	return myPOINT(idx % 10, idx / 10);
}

int tiles[2][100];
int tileCount[100];
int player;

void Print()
{
	cout << "player1" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 1)
			cout << "  ";
		for (int j = 0; j < 10; j++)
		{
			cout << (tiles[0][GetIdx(j, i)] == 1 ? "★  " : "■  ");
		}
		cout << endl;
	}
	cout << "player2" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 1)
			cout << "  ";
		for (int j = 0; j < 10; j++)
		{
			cout << (tiles[1][GetIdx(j, i)] == 1 ? "★  " : "■  ");
		}
		cout << endl;
	}
}
void Setting();
void Check();
void Reset();
int IsEnd();

int main()
{
	int count = 0;
	while (!GetAsyncKeyState(VK_SPACE) && count < 1)
	{
		Setting();
		Print();
		Reset();
		count++;
	}

	FILE* fp;
	fp = fopen("./data.txt", "w");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fprintf(fp, "%d\n", tileCount[GetIdx(j, i)]);
			cout << tileCount[GetIdx(j, i)] << "\t";
		}
		cout << endl;
	}
	fclose(fp);

	system("pause");
}

void Setting()
{
	random_device rd;
	seed = mt19937(rd());
	player = random(1, 2);

	const int maxSize = 5;
	for (int i = 0; i < 2; i++)
	{
		vector<int> sizeList = {2, 2, 3, 3, 4};
	REINPUT:
		int idx = random(0, sizeList.size() - 1);
		int size = sizeList[idx];
		int dir = random(0, 5);

		myPOINT startPos(random(0, 9), random(0, 9));

		startPos.x = startPos.x * 2 + startPos.y % 2;

		myPOINT ptList[maxSize];
		ptList[0] = startPos;
		if (tiles[i][GetIdx(startPos.x / 2, startPos.y)] == 1) goto REINPUT;
		for (int j = 1; j < size; j++)
		{
			startPos.x += *("124542" + dir) - '3';
			startPos.y += *("211233" + dir) - '2';
			if (startPos.x < 0 || startPos.y < 0 || startPos.x >= 20 || startPos.y >= 10) goto REINPUT;
			if (tiles[i][GetIdx(startPos.x / 2, startPos.y)] == 1) goto REINPUT;

			ptList[j] = startPos;
		}

		for (int j = 0; j < size; j++)
		{
			myPOINT pt = ptList[j];
			pt.x /= 2;
			tiles[i][GetIdx(pt)] = 1;
		}

		sizeList.erase(sizeList.begin() + idx);
		if (!sizeList.empty()) goto REINPUT;
	}
	//cout << "setting end" << endl;

	//Print();
	//system("pause");
}

void Check()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (tiles[i][j] == 1)
				tileCount[j]++;
		}
	}
}

void Reset()
{
	memset(tiles, 0, sizeof(tiles));
}

int IsEnd()
{
	for (int i = 0; i < 2; i++)
	{
		int j = 0;
		for (; j < 100; j++)
			if (tiles[i][j] == 1) break;
		if (j == 100)
			return i + 1;
	}
	return 0;
}