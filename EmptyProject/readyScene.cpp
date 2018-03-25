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

	background = IMAGEMANAGER->AddTexture("./image/map_sea.png", sTextureData(D3DXVECTOR2(0, 0)));
	backgroundIsland = IMAGEMANAGER->AddTexture("image/map_land.png", sTextureData(D3DXVECTOR2(0, 0)));
	sideBarUI = IMAGEMANAGER->AddTexture("./image/sideLine.png", sTextureData(D3DXVECTOR2(0, 0)));
	topBarUI = IMAGEMANAGER->AddTexture("./image/topLine.png", sTextureData(D3DXVECTOR2(0, 0)));
	itemBarUI = IMAGEMANAGER->AddTexture("./image/ui_item_bar.png", sTextureData(D3DXVECTOR2(0, 0)));
	timeBarUI = IMAGEMANAGER->AddTexture("./image/ui_time_bar.png", sTextureData(D3DXVECTOR2(0.5, 0)));

	for (int i = 0; i < 32; i++)
	{
		char str[128];
		sprintf(str, "./image/water/caust%02d.dds", i);
		auto result = water.emplace_back(IMAGEMANAGER->AddTexture(str, sTextureData(D3DXVECTOR2(0, 0))));

		D3DLOCKED_RECT rc;
		result->m_texturePtr->LockRect(0, &rc, nullptr, D3DLOCK_DISCARD);

		auto color = (DWORD*)rc.pBits;
		for (int j = 0; j < result->m_info.Width * result->m_info.Height; j++)
		{
			auto temp = (color[j] & 0x000000ff) / 2;
			color[j] = 0x01000000 * temp + 0x00ffffff;
		}

		result->m_texturePtr->UnlockRect(0);
	}

	m_playerObjs.push_back(Units(IMAGEMANAGER->AddTexture("./image/ship/player_1.png")));
	m_playerObjs.push_back(Units(IMAGEMANAGER->AddTexture("./image/ship/player_2.png")));
	m_playerObjs.push_back(Units(IMAGEMANAGER->AddTexture("./image/ship/player_3.png")));
	m_playerObjs.push_back(Units(IMAGEMANAGER->AddTexture("./image/ship/player_4.png")));
	m_playerObjs.push_back(Units(IMAGEMANAGER->AddTexture("./image/ship/player_5.png")));
	m_playerObjs.push_back(Units(IMAGEMANAGER->AddTexture("./image/ship/player_6.png")));
	m_playerObjs.push_back(Units(IMAGEMANAGER->AddTexture("./image/ship/player_7.png")));
	m_playerObjs.push_back(Units(IMAGEMANAGER->AddTexture("./image/ship/player_8.png")));
}


readyScene::~readyScene()
{
}

void readyScene::Init()
{
	settingEnd = false;
	m_playerTiles = unique_ptr<tiles>(new tiles());
	m_enemyTiles = unique_ptr<tiles>(new tiles());

	m_objs.push_back(make_pair(true, 2));
	m_objs.push_back(make_pair(true, 2));
	m_objs.push_back(make_pair(true, 3));
	m_objs.push_back(make_pair(true, 3));
	m_objs.push_back(make_pair(true, 4));

	selectShip = 0;
	nowDir = 0;
	rightSelect = false;

	m_cam.pos.y = 2000 - WINSIZEY / 2;
	m_cam.pos.x = WINSIZEX / 2;

	selectList.clear();
}

void readyScene::Release()
{
	ingame.lock()->SetTilesData(this->m_playerTiles, this->m_enemyTiles, this->m_playerArmy, this->m_enemyArmy);
}

void readyScene::Update(double dt)
{
	waterFrame = (int)(DXUTGetTime() * 30) % 32;

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
			m_playerTiles->SetTile(tileList);
			auto& result = m_playerArmy.emplace_back(cArmy(D3DXVECTOR2(0, 2000 - WINSIZEY)));
			for (auto iter : tileList)
			{
				m_playerObjs[selectShip].InitPos({ iter }, iter);
				result.AddUnit(m_playerObjs[selectShip]);
				m_playerObjs[selectShip].ResetPos();
			}

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
	background->Render(sprite, 0, 0, GetCamMatrix());
	
	int waterAlpha = 200 * pow(m_cam.scale, 3) + 55;
	if (waterAlpha > 200 + 55)
		waterAlpha = 200 + 55;
	
	for (int i = 0; i < 2000; i += 64)
	{
		for (int j = 0; j < WINSIZEX; j += 64)
			water[waterFrame]->Render(sprite, D3DCOLOR_ARGB(waterAlpha, 255, 255, 255), D3DXVECTOR2(j, i), GetCamMatrix());
	}
	
	backgroundIsland->Render(sprite, 0, 0, GetCamMatrix());

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
	for (auto iter : m_playerArmy)
	{
		iter.Render(sprite, 0, GetCamMatrix());
	}

	sideBarUI->Render(sprite, 0, 0);
	topBarUI->Render(sprite, 0, 0);
}
