#include "DXUT.h"
#include "readyScene.h"

#include "tiles.h"
#include "unit.h"
#include "gameScene.h"


readyScene::readyScene(weak_ptr<gameScene> ingame)
	:ingame(ingame)
{
	normalTile = IMAGEMANAGER->AddTexture("./image/map_floor_tile.png");
	selectTile = IMAGEMANAGER->AddTexture("./image/map_select_floor_tile.png");
}


readyScene::~readyScene()
{
}

void readyScene::Init()
{
	settingEnd = false;
	m_playerTiles = unique_ptr<tiles>(new tiles());
	m_enemyTiles = unique_ptr<tiles>(new tiles());

	m_playerArmy.push_back(cArmy(IMAGEMANAGER->AddTexture("./image/ship/player_1.png"), D3DXVECTOR2(0, 2000 - WINSIZEY)));

	for (int i = 0; i < 2; i++)
	{
		m_objs[i].push_back(make_pair(true, 2));
		m_objs[i].push_back(make_pair(true, 2));
		m_objs[i].push_back(make_pair(true, 3));
		m_objs[i].push_back(make_pair(true, 3));
		m_objs[i].push_back(make_pair(true, 4));
	}

	selectShip = 0;
	nowDir = 0;

	auto addUnit = Units({ 3, 3 });
	addUnit.units.push_back(unit(D3DXVECTOR2(0, 0)));
	m_playerArmy.front().AddUnit(addUnit);
}

void readyScene::Release()
{
	ingame.lock()->SetTilesData(this->m_playerTiles, this->m_enemyTiles, this->m_playerArmy, this->m_enemyAarmy);
}

void readyScene::Update(double dt)
{
	if(settingEnd)
		SCENEMANAGER->ChangeScene("game");

	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		nowDir = (++nowDir) % 6;

	nowPos = gameScene::SelectPos();

	auto [isCanSetIn, tileList] = m_playerTiles->IsSetInTile({ nowPos.x, nowPos.y }, m_objs[0][selectShip].second, (TILE_DIR)nowDir);
	if (isCanSetIn)
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			selectList.push({ nowPos.x + nowPos.y * 10, nowDir, selectShip });
			if (selectList.size() == m_objs[0].size())
				settingEnd = true;
		}
	}
	maybeList = std::move(tileList);
}

void readyScene::Render(LPD3DXSPRITE sprite)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			normalTile->Render(sprite, gameScene::GetTilePos(j, i) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2), GetCamMatrix());
		}
	}
	for (auto iter : maybeList)
	{
		selectTile->Render(sprite, gameScene::GetTilePos(iter.x, iter.y) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2), GetCamMatrix());
	}
}
