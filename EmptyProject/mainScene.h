#pragma once
#include "cScene.h"
class mainScene : public cScene
{
private:

public:
	mainScene();
	~mainScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(double dt) override;
	virtual void Render(LPD3DXSPRITE sprite) override;
};

