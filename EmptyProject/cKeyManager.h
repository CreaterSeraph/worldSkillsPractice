#pragma once
#include "singleton.h"
class cKeyManager : public singleton<cKeyManager>
{
private:
	bool nowKeyState[256];
	bool prevKeyState[256];
public:
	cKeyManager();
	~cKeyManager();

	void Update();
	bool IsOnceKeyDown(int key);
	bool IsStayKeyDown(int key);
	bool IsOnceKeyUp(int key);
};

#define KEYMANAGER cKeyManager::Get()