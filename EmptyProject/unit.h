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

struct Units
{
	vector<unit> units;

	bool isLive;
	POINT position;
};

class cArmy
{
private:
	vector<Units> vArmy;

	vector<shared_ptr<texture>> image;

};