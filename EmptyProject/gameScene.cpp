#include "DXUT.h"
#include "gameScene.h"

#include "tiles.h"
#include "unit.h"

gameScene::gameScene()
	:camAction(this->m_cam)
{
	background = IMAGEMANAGER->AddTexture("./image/map_sea.png", sTextureData(D3DXVECTOR2(0, 0)));
	backgroundIsland = IMAGEMANAGER->AddTexture("image/map_land.png", sTextureData(D3DXVECTOR2(0, 0)));
	sideBarUI = IMAGEMANAGER->AddTexture("./image/sideLine.png", sTextureData(D3DXVECTOR2(0, 0)));
	topBarUI = IMAGEMANAGER->AddTexture("./image/topLine.png", sTextureData(D3DXVECTOR2(0, 0)));
	itemBarUI = IMAGEMANAGER->AddTexture("./image/ui_item_bar.png", sTextureData(D3DXVECTOR2(0, 0)));
	timeBarUI = IMAGEMANAGER->AddTexture("./image/ui_time_bar.png", sTextureData(D3DXVECTOR2(0.5, 0)));

	normalTile = IMAGEMANAGER->AddTexture("./image/map_floor_tile.png");
	selectTile = IMAGEMANAGER->AddTexture("./image/map_select_floor_tile.png");
	selectArrow = IMAGEMANAGER->AddTexture("./image/map_select_arrow.png");

	vCloud.push_back(IMAGEMANAGER->AddTexture("./image/map_cloud.png"));

	vMovingCloud[0] = IMAGEMANAGER->AddTexture("./image/map_moving_claud_1.png");
	vMovingCloud[1] = IMAGEMANAGER->AddTexture("./image/map_moving_claud_2.png");
	vMovingCloud[2] = IMAGEMANAGER->AddTexture("./image/map_moving_claud_3.png");

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
}


gameScene::~gameScene()
{
}

void gameScene::Init()
{
	playerTurn = true;
	gameReady = false;
	selectIdx = -1;

	camStartPos.y = 2000 - WINSIZEY / 2;
	camStartPos.x = WINSIZEX / 2;
	camEndPos.y = 90 + WINSIZEY / 2;
	camEndPos.x = WINSIZEX / 2;

	m_cam.pos = (camStartPos + camEndPos) / 2;

	auto func = [](float t, const CamData& start, const CamData& end)->CamData
	{
		CamData result;

		D3DXVec2Lerp(&result.pos, &start.pos, &end.pos, pow(1 - t, 3));

		return result;
	};
	camAction.AddAction(func, 1, camEndPos);
	swap(camEndPos, camStartPos);

	sideBarPos = D3DXVECTOR2(0, 0);
}

void gameScene::Release()
{
}

void gameScene::Update(double dt)
{
	waterFrame = (int)(DXUTGetTime() * 30) % 32;
	if (!camAction.Update(dt))
	{
		gameReady = true;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0;j<vMovingCloudePos[i].size();j++)
		{
			auto& iter = vMovingCloudePos[i][j];
			iter.x += (75 + 25 * i) * dt;

			if (iter.x > WINSIZEX + 200)
			{
				vMovingCloudePos[i].erase(vMovingCloudePos[i].begin() + j);
			}
		}
	}

	if (waterFrame == 0)
	{
		vMovingCloudePos[RAND->Rand(0, 2)].push_back(D3DXVECTOR2(RAND->Rand(-200, -100), RAND->Rand(0, 2000)));
	}

	if (KEYMANAGER->IsStayKeyDown(VK_UP))
		m_cam.scale += dt;
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
		m_cam.scale /= 1 + dt;
	if (gameReady)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			MoveCamToOtherPlayer();
		}
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			POINT pt = SelectPos();
			size_t idx = GetIdx(pt);
			if (selectIdx == -1)
				selectIdx = idx;
			else if (selectIdx == idx)
			{
				bool result;
				if(playerTurn)
					result = m_enemyTiles->HitTile(selectIdx);
				else
					result = m_playerTiles->HitTile(selectIdx);
				
				selectIdx = -1;
				if (result)
					MoveCamToOtherPlayer();
			}
			else
				selectIdx = idx;
		}
	}
}

POINT gameScene::SelectPos()
{
	float distance = 9999;
	POINT pt;

	int min = -1;
	int max = 11;

	pt.x = min - 1;
	pt.y = min - 1;

	for (int i = min; i < max; i++)
	{
		for (int j = min; j < max; j++)
		{
			auto temp = D3DXVec2Length(&(D3DXVECTOR2(ptMouse.x, ptMouse.y) - D3DXVECTOR2(300 + j * 72 + ((unsigned)i % 2) * 36, 130 + i * 61)));
			if (temp < distance)
			{
				distance = temp;
				pt.x = j;
				pt.y = i;
			}
		}
	}
	return pt;
}

D3DXVECTOR2 gameScene::GetTilePos(size_t idx)
{
	return GetTilePos(idx % 10, idx / 10);
}

D3DXVECTOR2 gameScene::GetTilePos(int x, int y)
{
	return D3DXVECTOR2(300 + x * 72 + ((unsigned)y % 2) * 36, 130 + y * 61);
}

int gameScene::GetIdx(const POINT& pt)
{
	if (pt.x < 0 || pt.x >= 10 || pt.y < 0 || pt.y >= 10)
		return -1;
	else
		return pt.x + pt.y * 10;
}

void gameScene::MoveCamToOtherPlayer()
{
	auto func = [](float t, const CamData& start, const CamData& end)->CamData
	{
		CamData result;

		D3DXVec2Lerp(&result.pos, &start.pos, &end.pos, pow(1 - t, 3));

		return result;
	};
	camAction.AddAction(func, 1, camEndPos);

	playerTurn = playerTurn ? false : true;
	gameReady = false;
	selectIdx = -1;
	swap(camEndPos, camStartPos);
}

void gameScene::Render(LPD3DXSPRITE sprite)
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

	auto time = DXUTGetTime();
	for (auto iter : m_playerArmy)
	{
		iter.Render(sprite, time, GetCamMatrix());
	}

	for (auto iter : m_enemyArmy)
	{
		iter.Render(sprite, time, GetCamMatrix());
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_enemyTiles->CheckTile(i * 10 + j) == TS_NORMAL)
				vCloud[0]->Render(sprite, GetTilePos(j, i) + D3DXVECTOR2(0, 90), GetCamMatrix());
		}
	}

	int cloudeAlpha = 200 / pow(m_cam.scale, 2);
	if (cloudeAlpha > 255)
		cloudeAlpha = 255;

	for (int i = 0; i < 3; i++)
	{
		for (auto iter : vMovingCloudePos[i])
		{
			vMovingCloud[i]->Render(sprite, D3DCOLOR_ARGB(cloudeAlpha, 255, 255, 255), iter, GetCamMatrix());
		}
	}

	if (gameReady)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				D3DXVECTOR2 distance(GetTilePos(j, i) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2) - D3DXVECTOR2(ptMouse.x, ptMouse.y + m_cam.pos.y - WINSIZEY / 2));
				
				if (D3DXVec2Length(&distance) < 100)
					normalTile->Render(sprite, GetTilePos(j, i) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2), GetCamMatrix());
				else if (selectIdx == i * 10 + j)
					selectIdx = -1;
			}
		}
		if (selectIdx != -1)
		{
			selectArrow->Render(sprite, GetTilePos(selectIdx) + D3DXVECTOR2(0, sin(DXUTGetTime() * 5) * 20 + m_cam.pos.y - WINSIZEY / 2 - 50), GetCamMatrix());
			selectTile->Render(sprite, GetTilePos(selectIdx) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2), GetCamMatrix());
		}
	}
	
	//itemBarUI->Render(sprite, 0, 0);
	sideBarUI->Render(sprite, sideBarPos);
	topBarUI->Render(sprite, 0, 0);
	//timeBarUI->Render(sprite, WINSIZEX / 2, 40);

	font temp("굴림");
	temp.Print(sprite, 0, 0, "출력되니?");
}

void gameScene::SetTilesData(unique_ptr<tiles>& playerTile, unique_ptr<tiles>& enemyTile, vector<cArmy>& playerArmy, vector<cArmy>& enemyArmy)
{
	m_playerTiles = std::move(playerTile);
	m_enemyTiles = std::move(enemyTile);
	m_playerArmy = std::move(playerArmy);
	m_enemyArmy = std::move(enemyArmy);
}

CamAction::CamAction(function<CamData(float, const CamData&, const CamData&)> func, float time, const CamData& endPos, CamData& nowPos)
	:func(func), maxTime(time), nowTime(time), endPos(endPos), startPos(), nowPos(nowPos)
{
}

bool CamAction::Update(double dt)
{
	nowTime -= dt;
	if (nowTime < 0)
	{
		nowPos = endPos;
		return false;
	}
	nowPos = func(nowTime / maxTime, startPos, endPos);
	return true;
}

void CamAction::SetStartPos(const CamData& camData)
{
	startPos = camData;
}

CamActionAdmin::CamActionAdmin(CamData& nowPos)
	:nowPos(nowPos)
{
}

bool CamActionAdmin::Update(double dt)
{
	if (actionQueue.empty()) return false;
	
	if (actionQueue.front().Update(dt)) return true;

	actionQueue.pop();
	if (actionQueue.empty()) return true;

	actionQueue.front().SetStartPos(nowPos);
	return true;
}

void CamActionAdmin::AddAction(function<CamData(float, const CamData&, const CamData&)> func, float time, const CamData& endPos)
{
	actionQueue.push(CamAction(func, time, endPos, nowPos));
	actionQueue.back().SetStartPos(nowPos);
}
