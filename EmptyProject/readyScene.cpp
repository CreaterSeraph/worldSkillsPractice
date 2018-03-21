#include "DXUT.h"
#include "readyScene.h"

#include "tiles.h"
#include "gameScene.h"

readyScene::readyScene(weak_ptr<gameScene> ingame)
	:ingame(ingame)
{
}


readyScene::~readyScene()
{
}

void readyScene::Init()
{
	settingEnd = true;
	m_playerTiles = unique_ptr<tiles>(new tiles());
	m_enemyTiles = unique_ptr<tiles>(new tiles());
}

void readyScene::Release()
{
	ingame.lock()->SetTilesData(this->m_playerTiles, this->m_enemyTiles);
}

void readyScene::Update(double dt)
{
	if(settingEnd)
		SCENEMANAGER->ChangeScene("game");
}

void readyScene::Render(LPD3DXSPRITE sprite)
{
}
