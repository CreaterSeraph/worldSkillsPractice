#include "DXUT.h"
#include "gameScene.h"

#include "tiles.h"

gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

void gameScene::Init()
{
	background = IMAGEMANAGER->AddTexture("./image/map.png", sTextureData(D3DXVECTOR2(0, 0)));
	itemBarUI = IMAGEMANAGER->AddTexture("./image/ui_item_bar.png", sTextureData(D3DXVECTOR2(0, 0)));
	timeBarUI = IMAGEMANAGER->AddTexture("./image/ui_time_bar.png", sTextureData(D3DXVECTOR2(0.5, 0)));
}

void gameScene::Release()
{
}

void gameScene::Update(double dt)
{
	m_camPos.y -= 50 * dt;
}

void gameScene::Render(LPD3DXSPRITE sprite)
{
	background->Render(sprite, 0, 0, GetCamMaxtrix());
	itemBarUI->Render(sprite, 0, 0);
	timeBarUI->Render(sprite, WINSIZEX / 2, 40);
}

void gameScene::SetTilesData(unique_ptr<tiles>& playerTile, unique_ptr<tiles>& enemyTile)
{
	m_playerTiles = std::move(playerTile);
	m_enemyTiles = std::move(enemyTile);
}
