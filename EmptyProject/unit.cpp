#include "DXUT.h"
#include "unit.h"


unit::unit(size_t maxFrame, const D3DXVECTOR2& offset, double maxDelay, double minDelay)
	:maxFrame(maxFrame), offset(offset), maxDelay(maxDelay), minDelay(minDelay), frame(0), frameTime(0)
{
}

unit::~unit()
{
}

void unit::Update(double dt)
{
	frameTime -= dt;
	if (frameTime < 0)
	{
		frame++;
		if (frame == maxFrame)
			frame = 0;
		frameTime = maxDelay;
	}
}