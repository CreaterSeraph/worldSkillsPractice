// testConsol.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct POINT
{
	int x, y;
	POINT()
		:x(0), y(0)
	{
	}
	POINT(int x, int y)
		:x(x), y(y)
	{
	}
};

int tiles[100];

int GetIdx(int x, int y)
{
	return y * 10 + x;
}

int GetIdx(const POINT& pt)
{
	return pt.y * 10 + pt.x;
}

POINT GetPt(int idx)
{
	return POINT(idx % 10, idx / 10);
}

void Print()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j+=2)
		{
			cout << (tiles[GetIdx(j, i)] ? "ㅁ  " : "ㅇ  ");
		}
		cout << endl;
		for (int j = 1; j < 10; j+=2)
		{
			cout << (tiles[GetIdx(j, i)] ? "  ㅁ": "  ㅇ");
		}
		cout << endl;
	}
}

int main()
{
	const int maxSize = 5;
	int quit;
	int size;
	int dir;
	do
	{
		REINPUT:
		system("cls");

		POINT startPos;
		cin >> startPos.x >> startPos.y;
		startPos.y = startPos.y * 2 + startPos.x % 2;
		if (startPos.x < 0 || startPos.y < 0 || startPos.x >= 10 || startPos.y >= 20) goto REINPUT;
		cin >> size;
		if (size > maxSize + 1) goto REINPUT;
		cin >> dir;
		if (dir > 6 || dir < 0) goto REINPUT;

		POINT ptList[maxSize];
		ptList[0] = startPos;
		for (int i = 1; i < size; i++)
		{
			startPos.x += *("bccbaa" + dir) - 'b';
			startPos.y += *("abdedb" + dir) - 'c';
			if (startPos.x < 0 || startPos.y < 0 || startPos.x >= 10 || startPos.y >= 20) goto REINPUT;

			ptList[i] = startPos;
		}

		for (int i = 0; i < size; i++)
		{
			POINT pt = ptList[i];
			pt.y /= 2;
			tiles[GetIdx(pt)] = 1;
		}

		Print();
		cin >> quit;
	} while (quit);
    return 0;
}

