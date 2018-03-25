#pragma once
#include "cScene.h"
class tiles;
class gameScene;
class cArmy;
struct Units;
class readyScene : public cScene
{
private:
	unique_ptr<tiles> m_playerTiles;
	unique_ptr<tiles> m_enemyTiles;

	vector<cArmy> m_playerArmy;
	vector<cArmy> m_enemyArmy;

	vector<Units> m_playerObjs;

	weak_ptr<gameScene> ingame;

	shared_ptr<texture> normalTile;
	shared_ptr<texture> selectTile;
	shared_ptr<texture> rightTile;

	shared_ptr<texture> background;
	shared_ptr<texture> backgroundIsland;

	shared_ptr<texture> topBarUI;
	shared_ptr<texture> sideBarUI;
	shared_ptr<texture> itemBarUI;
	shared_ptr<texture> timeBarUI;

	vector<shared_ptr<texture>> water;
	int waterFrame;

	vector<pair<bool, size_t>> m_objs;

	//pos, dir, sizeIdx
	vector<vector<POINT>> selectList;
	POINT nowPos;
	int nowDir;
	int selectShip;
	vector<POINT> maybeList;
	bool rightSelect;

	bool settingEnd;
private:
	void EnemySetting();
	POINT AddPt(const POINT& pt1, const POINT& pt2);
public:
	readyScene(weak_ptr<gameScene> ingame);
	~readyScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(double dt) override;
	virtual void Render(LPD3DXSPRITE sprite) override;
};

