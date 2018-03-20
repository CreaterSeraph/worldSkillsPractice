#pragma once
struct unit
{
	vector<shared_ptr<texture>> vFrameImage;
	size_t frame;
	double frameTime;

	double maxDelay;
	double minDelay;
	D3DXVECTOR2 offset;

	unit(const vector<shared_ptr<texture>>& frameImage, const D3DXVECTOR2& offset, double maxDelay, double minDelay);
	~unit();
};