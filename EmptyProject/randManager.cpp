#include "DXUT.h"
#include "randManager.h"


randManager::randManager()
{
	random_device rd;
	seed = mt19937(rd());
}


randManager::~randManager()
{
}

template<>
double randManager::Rand(double min, double max)
{
	uniform_real_distribution<double> dist(min, max);
	return dist(seed);
}

template<>
float randManager::Rand(float min, float max)
{
	uniform_real_distribution<float> dist(min, max);
	return dist(seed);
}

template<>
int randManager::Rand(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(seed);
}