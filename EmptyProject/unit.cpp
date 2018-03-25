#include "DXUT.h"
#include "unit.h"
#include "gameScene.h"

Units::Units(shared_ptr<texture> image, shared_ptr<texture> deathImage)
	:image(image), deathImage(deathImage)
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
	if (ptList.empty())
	{
		if(deathImage)
			deathImage->Render(sprite, gameScene::GetTilePos(renderPos.x, renderPos.y) + pos, mat);
	}
	else
	{
		if(image)
			image->Render(sprite, gameScene::GetTilePos(renderPos.x, renderPos.y) + pos, mat);
	}
}

bool Units::Hit(const POINT& pt)
{
	for (int i = 0; i < ptList.size(); i++)
	{
		auto iter = ptList[i];
		if (iter.x == pt.x && iter.y == pt.y)
		{
			ptList.erase(ptList.begin() + i);
			return true;
		}
	}
	return false;
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

bool cArmy::Hit(const POINT& pt)
{
	for (auto& iter : vArmy)
	{
		if (iter.Hit(pt))
			return true;
	}
	
	return false;
}
