#include "DXUT.h"
#include "gameScene.h"

#include "tiles.h"

gameScene::gameScene()
{
	background = IMAGEMANAGER->AddTexture("./image/map.png", sTextureData(D3DXVECTOR2(0, 0)));
	sideBarUI = IMAGEMANAGER->AddTexture("./image/sideLine.png", sTextureData(D3DXVECTOR2(0, 0)));
	topBarUI = IMAGEMANAGER->AddTexture("./image/topLine.png", sTextureData(D3DXVECTOR2(0, 0)));
	itemBarUI = IMAGEMANAGER->AddTexture("./image/ui_item_bar.png", sTextureData(D3DXVECTOR2(0, 0)));
	timeBarUI = IMAGEMANAGER->AddTexture("./image/ui_time_bar.png", sTextureData(D3DXVECTOR2(0.5, 0)));

	normalTile = IMAGEMANAGER->AddTexture("./image/map_floor_tile.png");
	selectTile = IMAGEMANAGER->AddTexture("./image/map_select_floor_tile.png");
	selectArrow = IMAGEMANAGER->AddTexture("./image/map_select_arrow.png");

	vCloud.push_back(shared_ptr<texture>(IMAGEMANAGER->AddTexture("./image/map_cloud.png")));
}


gameScene::~gameScene()
{
}

void gameScene::Init()
{
	playerTurn = true;
	gameReady = false;

	camStartPos.y = 2000 - WINSIZEY / 2;
	camStartPos.x = WINSIZEX / 2;
	camEndPos.y = 90 + WINSIZEY / 2;
	camEndPos.x = WINSIZEX / 2;
	moveProgress = 1;
	selectIdx = -1;

	sideBarPos = D3DXVECTOR2(0, 0);
}

void gameScene::Release()
{
}

void gameScene::Update(double dt)
{
	if (moveProgress)
	{
		D3DXVec2Lerp(&m_cam.pos, &camStartPos, &camEndPos, pow(moveProgress.value(), 3));

		moveProgress.value() += dt;
		if (moveProgress.value() > 1)
		{
			gameReady = true;
			moveProgress.reset();

			m_cam.pos = camEndPos;
			swap(camEndPos, camStartPos);
		}
	}

	if (KEYMANAGER->IsStayKeyDown(VK_UP))
	{
		m_cam.scale /= 1 + dt;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN))
	{
		m_cam.scale += dt;
	}

	if (gameReady)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			playerTurn = playerTurn ? false : true;
			moveProgress = 0;
			gameReady = false;
			selectIdx = -1;
		}
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			size_t idx = SelectPos();
			if (selectIdx == -1)
				selectIdx = idx;
			else if (selectIdx == idx)
			{
				if(playerTurn)
					m_enemyTiles->HitTile(selectIdx);
				else
					m_playerTiles->HitTile(selectIdx);
				selectIdx = -1;

				playerTurn = playerTurn ? false : true;
				moveProgress = 0;
				gameReady = false;
				selectIdx = -1;
			}
			else
				selectIdx = idx;
		}
	}
}

int gameScene::SelectPos()
{
	float distance = 9999;
	POINT pt;
	pt.x = -1;
	pt.y = -1;

	for (int i = -1; i < 11; i++)
	{
		for (int j = -1; j < 11; j++)
		{
			auto temp = D3DXVec2Length(&(D3DXVECTOR2(ptMouse.x, ptMouse.y) - D3DXVECTOR2(300 + j * 72 + ((i + 1) % 2) * 36, 130 + i * 61)));
			if (temp < distance)
			{
				distance = temp;
				pt.x = j;
				pt.y = i;
			}
		}
	}
	if (pt.x == -1 || pt.x == 10 || pt.y == -1 || pt.y == 10)
		return -1;
	return pt.x + pt.y * 10;
}

D3DXVECTOR2 gameScene::GetTilePos(size_t idx)
{
	return GetTilePos(idx % 10, idx / 10);
}

D3DXVECTOR2 gameScene::GetTilePos(int x, int y)
{
	return D3DXVECTOR2(300 + x * 72 + ((y + 1) % 2) * 36, 130 + y * 61);
}

void gameScene::Render(LPD3DXSPRITE sprite)
{
	background->Render(sprite, 0, 0, GetCamMaxtrix());

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_enemyTiles->CheckTile(i * 10 + j) == TS_NORMAL)
				vCloud[0]->Render(sprite, GetTilePos(j, i) + D3DXVECTOR2(0, 90), GetCamMaxtrix());
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
					normalTile->Render(sprite, GetTilePos(j, i) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2), GetCamMaxtrix());
				else if (selectIdx == i * 10 + j)
					selectIdx = -1;
			}
		}
		if (selectIdx != -1)
		{
			selectArrow->Render(sprite, GetTilePos(selectIdx) + D3DXVECTOR2(0, sin(DXUTGetTime() * 5) * 20 + m_cam.pos.y - WINSIZEY / 2 - 50), GetCamMaxtrix());
			selectTile->Render(sprite, GetTilePos(selectIdx) + D3DXVECTOR2(0, m_cam.pos.y - WINSIZEY / 2), GetCamMaxtrix());
		}
	}
	
	//itemBarUI->Render(sprite, 0, 0);
	sideBarUI->Render(sprite, sideBarPos);
	topBarUI->Render(sprite, 0, 0);
	//timeBarUI->Render(sprite, WINSIZEX / 2, 40);

	font temp("굴림");
	temp.Print(sprite, 0, 0, "출력되니?");
}

void gameScene::SetTilesData(unique_ptr<tiles>& playerTile, unique_ptr<tiles>& enemyTile)
{
	m_playerTiles = std::move(playerTile);
	m_enemyTiles = std::move(enemyTile);
}