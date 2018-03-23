#include "DXUT.h"
#include "unit.h"
#include "gameScene.h"

unit::unit(const D3DXVECTOR2& offset)
	:offset(offset)
{
}

unit::~unit()
{
}

void unit::Render(LPD3DXSPRITE sprite, weak_ptr<texture> renderTexture, const D3DXVECTOR2& pos, double time, const D3DXMATRIX& mat)
{
	cTransform transform(pos + offset, 0xffffffff, false, D3DXVECTOR2(0.8, 0.8));
	renderTexture.lock()->Render(sprite, transform, mat);
}

void Units::Render(LPD3DXSPRITE sprite, weak_ptr<texture> renderTexture, const D3DXVECTOR2& pos, double time, const D3DXMATRIX& mat)
{
	auto sortFunc = [](const unit& u1, const unit& u2)->bool {
		return u1.offset.y < u2.offset.y;
	};

	std::sort(units.begin(), units.end(), sortFunc);

	for (auto iter : units)
	{
		iter.Render(sprite, renderTexture, pos + gameScene::GetTilePos(position.x, position.y), time, mat);
	}
}

Units::Units(const POINT& pt)
	:position(pt)
{
}

cArmy::cArmy(shared_ptr<texture> image, const D3DXVECTOR2& pos)
	:image(image), startPos(pos)
{
}

void cArmy::Render(LPD3DXSPRITE sprite, double time, const D3DXMATRIX& mat)
{
	auto sortFunc = [](const Units& u1, const Units& u2)->bool {
		return u1.position.y < u2.position.y;
	};

	std::sort(vArmy.begin(), vArmy.end(), sortFunc);

	for (auto iter : vArmy)
		iter.Render(sprite, image, startPos, time, mat);
}

void cArmy::AddUnit(const Units& unit)
{
	vArmy.push_back(unit);
}
