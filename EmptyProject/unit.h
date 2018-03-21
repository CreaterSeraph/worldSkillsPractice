#pragma once
struct unit
{
	const size_t maxFrame;
	size_t frame;
	double frameTime;

	double maxDelay;
	double minDelay;
	D3DXVECTOR2 offset;

	unit(size_t maxFrame, const D3DXVECTOR2& offset, double maxDelay, double minDelay);
	~unit();

	void Update(double dt);
};

class Units
{
	vector<unit> units;
};