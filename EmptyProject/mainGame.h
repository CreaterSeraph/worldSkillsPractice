#pragma once
class mainGame
{
private:
	LPD3DXSPRITE sprite;
public:
	mainGame();
	~mainGame();

	void Init();
	void Release();
	void Update(double dt);
	void Render();
	void LostDevice();
	void ResetDevice();
};

