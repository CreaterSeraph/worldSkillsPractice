#pragma once
#include "cScene.h"
class tiles;
class gameScene;
class cArmy;
class readyScene : public cScene
{
private:
	unique_ptr<tiles> m_playerTiles;
	unique_ptr<tiles> m_enemyTiles;

	vector<cArmy> m_playerArmy;
	vector<cArmy> m_enemyAarmy;

	weak_ptr<gameScene> ingame;

	shared_ptr<texture> normalTile;
	shared_ptr<texture> selectTile;

	vector<pair<bool, size_t>> m_objs[2];

	//pos, dir, sizeIdx
	stack<tuple<int, int, int>> selectList;
	POINT nowPos;
	int nowDir;
	int selectShip;
	vector<POINT> maybeList;

	bool settingEnd;
public:
	readyScene(weak_ptr<gameScene> ingame);
	~readyScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(double dt) override;
	virtual void Render(LPD3DXSPRITE sprite) override;
};

