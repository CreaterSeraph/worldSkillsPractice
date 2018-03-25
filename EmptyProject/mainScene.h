#pragma once
#include "cScene.h"
class cButton;
class mainScene : public cScene
{
private:
	unique_ptr<cButton> btExit;
	unique_ptr<cButton> btHow;
	unique_ptr<cButton> btStart;

	shared_ptr<texture> howToPlay;
	shared_ptr<texture> backGround;
	shared_ptr<texture> backGroundani;
	bool popUp;
public:
	mainScene();
	~mainScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(double dt) override;
	virtual void Render(LPD3DXSPRITE sprite) override;
};

