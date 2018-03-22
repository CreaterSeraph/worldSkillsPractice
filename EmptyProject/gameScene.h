#pragma once
#include "cScene.h"

class CamAction
{
private:
	CamData& nowPos;
	CamData startPos;
	CamData endPos;

	float maxTime;
	float nowTime;
	
	function<CamData(float, const CamData&, const CamData&)> func;
public:
	CamAction(function<CamData(float, const CamData&, const CamData&)> func, float time, const CamData& endPos, CamData& nowPos);
	bool Update(double dt);
	void SetStartPos(const CamData& camData);
};

class CamActionAdmin
{
private:
	CamData& nowPos;
	queue<CamAction> actionQueue;
public:
	CamActionAdmin(CamData& nowPos);
	bool Update(double dt);

	void AddAction(function<CamData(float, const CamData&, const CamData&)> func, float time, const CamData& endPos);
};

class tiles;
class gameScene : public cScene
{
private:
	unique_ptr<tiles> m_playerTiles;
	unique_ptr<tiles> m_enemyTiles;

	shared_ptr<texture> background;
	shared_ptr<texture> backgroundIsland;

	shared_ptr<texture> topBarUI;
	shared_ptr<texture> sideBarUI;
	shared_ptr<texture> itemBarUI;
	D3DXVECTOR2 sideBarPos;

	shared_ptr<texture> timeBarUI;

	shared_ptr<texture> normalTile;
	shared_ptr<texture> selectTile;
	shared_ptr<texture> selectArrow;
	vector<shared_ptr<texture>> vCloud;

	//unique_ptr<texture> cloudTexture;

	CamActionAdmin camAction;

	bool playerTurn;
	bool gameReady;

	int selectIdx;

	D3DXVECTOR2 camStartPos;
	D3DXVECTOR2 camEndPos;

	vector<shared_ptr<texture>> water;
	int waterFrame;
private:
	int SelectPos();
	void MoveCamToOtherPlayer();
public:
	static D3DXVECTOR2 GetTilePos(size_t idx);
	static D3DXVECTOR2 GetTilePos(int x, int y);
public:
	gameScene();
	~gameScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(double dt) override;
	virtual void Render(LPD3DXSPRITE sprite) override;

	void SetTilesData(unique_ptr<tiles>& playerTile, unique_ptr<tiles>& enemyTile);
};

