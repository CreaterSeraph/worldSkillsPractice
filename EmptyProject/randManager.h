#pragma once
#include "singleton.h"
class randManager : public singleton<randManager>
{
private:
	mt19937 seed;
public:
	randManager();
	~randManager();

	template<typename T>
	T Rand(T min, T max);
};

#define RAND randManager::Get()