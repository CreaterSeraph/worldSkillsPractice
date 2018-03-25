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
	rightTile = IMAGEMANAGER->AddTexture("./image/map_floor_current.png");
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

	m_objs.push_back(make_pair(true, 2));
	m_objs.push_back(make_pair(true, 2));
	m_objs.push_back(make_pair(true, 3));
	m_objs.push_back(make_pair(true, 3));
	m_objs.push_back(make_pair(true, 4));

	selectShip = 0;
	nowDir = 0;
	rightSelect = false;

	selectList.clear();
}

void readyScene::Release()
{
	ingame.lock()->SetTilesData(this->m_playerTiles, this->m_enemyTiles, this->m_playerArmy, this->m_enemyArmy);
}

void readyScene::Update(double dt)
{
	if(settingEnd)
		SCENEMANAGER->ChangeScene("game");

	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))
		nowDir = (++nowDir) % 6;

	nowPos = gameScene::SelectPos();

	if (!m_objs[selectShip].first) return;
	auto [isCanSetIn, tileList] = m_playerTiles->IsSetInTile({ nowPos.x, nowPos.y }, m_objs[selectShip].second, (TILE_DIR)nowDir);
	if (isCanSetIn)
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			selectList.push_back(tileList);
			m_playerTiles->SetTile(std::move(tileList));

			m_objs[selectShip].first = false;
			for (int i = 0; i < m_objs.size(); i++)
			{
				if (m_objs[i].first)
				{
					selectShip = i;
					break;
				}
			}

			if (selectList.size() == m_objs.size())
				settingEnd = true;
		}
	}
	maybeList = std::move(tileList);
	rightSelect = isCanSetIn;
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
		if(rightSelect)
			rightTile->Render(sprite, gameScene::GetTilePos(iter.x, iter.y) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2), GetCamMatrix());
		else
			selectTile->Render(sprite, gameScene::GetTilePos(iter.x, iter.y) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2), GetCamMatrix());
	}
	for (auto iter : selectList)
	{
		for (auto iter2 : iter)
		{
			bool find = false;
			for (auto iterMaybe : maybeList)
			{
				if (iterMaybe.x == iter2.x && iterMaybe.y == iter2.y)
					find = true;
			}
			if(!find)
				rightTile->Render(sprite, gameScene::GetTilePos(iter2.x, iter2.y) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2), GetCamMatrix());
		}
	}
}
