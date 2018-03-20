#include "DXUT.h"
#include "unit.h"


unit::unit(const vector<shared_ptr<texture>>& frameImage, const D3DXVECTOR2& offset, double maxDelay, double minDelay)
	:vFrameImage(frameImage), offset(offset), maxDelay(maxDelay), minDelay(minDelay), frame(0), frameTime(0)
{
}

unit::~unit()
{
}
