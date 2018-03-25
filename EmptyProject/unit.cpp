#include "DXUT.h"
#include "unit.h"
#include "gameScene.h"

Units::Units(shared_ptr<texture> image)
	:image(image)
{
}

void Units::InitPos(const vector<POINT>& ptList, const POINT& renderPos)
{
	this->ptList = ptList;
	this->renderPos = renderPos;
}

void Units::ResetPos()
{
	this->ptList.clear();
}

void Units::Render(LPD3DXSPRITE sprite, const D3DXVECTOR2& pos, double time, const D3DXMATRIX& mat)
{
	image->Render(sprite, gameScene::GetTilePos(renderPos.x, renderPos.y) + pos, mat);
}

cArmy::cArmy(const D3DXVECTOR2& pos)
	:startPos(pos)
{
}

void cArmy::Render(LPD3DXSPRITE sprite, double time, const D3DXMATRIX& mat)
{
	auto sortFunc = [](const Units& u1, const Units& u2)->bool {
		return u1.renderPos.y < u2.renderPos.y;
	};

	std::sort(vArmy.begin(), vArmy.end(), sortFunc);

	for (auto iter : vArmy)
		iter.Render(sprite, startPos, time, mat);
}

void cArmy::AddUnit(const Units& unit)
{
	vArmy.push_back(unit);
}
