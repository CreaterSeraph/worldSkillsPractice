#include "DXUT.h"
#include "cKeyManager.h"


cKeyManager::cKeyManager()
{
	ZeroMemory(nowKeyState, 256);
	ZeroMemory(prevKeyState, 256);
}


cKeyManager::~cKeyManager()
{
}

void cKeyManager::Update()
{
	memcpy(prevKeyState, nowKeyState, 256);

	for (int i = 0; i < 256; i++)
	{
		nowKeyState[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

bool cKeyManager::IsOnceKeyDown(int key)
{
	return nowKeyState[key] && !prevKeyState[key];
}

bool cKeyManager::IsStayKeyDown(int key)
{
	return nowKeyState[key];
}

bool cKeyManager::IsOnceKeyUp(int key)
{
	return !nowKeyState[key] && prevKeyState[key];
}
