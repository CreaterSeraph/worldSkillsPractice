#include "DXUT.h"
#include "unit.h"
#include "gameScene.h"

Units::Units(vector<POINT>&& ptList, const POINT& renderPos)
	:ptList(ptList), renderPos(renderPos)
{
}

void Units::Render(LPD3DXSPRITE sprite, weak_ptr<texture> renderTexture, const D3DXVECTOR2& pos, double time, const D3DXMATRIX& mat)
{
	renderTexture.lock()->Render(sprite, gameScene::GetTilePos(renderPos.x, renderPos.y) + pos, mat);
}

cArmy::cArmy(shared_ptr<texture> image, const D3DXVECTOR2& pos)
	:image(image), startPos(pos)
{
}

void cArmy::Render(LPD3DXSPRITE sprite, double time, const D3DXMATRIX& mat)
{
	auto sortFunc = [](const Units& u1, const Units& u2)->bool {
		return u1.renderPos.y < u2.renderPos.y;
	};

	std::sort(vArmy.begin(), vArmy.end(), sortFunc);

	for (auto iter : vArmy)
		iter.Render(sprite, image, startPos, time, mat);
}

void cArmy::AddUnit(const Units& unit)
{
	vArmy.push_back(unit);
}
