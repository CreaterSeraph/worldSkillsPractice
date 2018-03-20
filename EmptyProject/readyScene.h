#pragma once
#include "cScene.h"
class tiles;
class gameScene;
class readyScene : public cScene
{
private:
	unique_ptr<tiles> m_playerTiles;
	unique_ptr<tiles> m_enemyTiles;

	weak_ptr<gameScene> ingame;

	bool settingEnd;
public:
	readyScene(weak_ptr<gameScene> ingame);
	~readyScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(double dt) override;
	virtual void Render(LPD3DXSPRITE sprite) override;
};

