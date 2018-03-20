#include "DXUT.h"
#include "mainGame.h"
#include "mainScene.h"

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

void mainGame::Init()
{
	D3DXCreateSprite(Device, &sprite);

	SCENEMANAGER->AddScene("main", shared_ptr<cScene>(new mainScene));
	SCENEMANAGER->ChangeScene("main");
}

void mainGame::Release()
{
	SAFE_RELEASE(sprite);
}

void mainGame::Update(double dt)
{
	SCENEMANAGER->Update(dt);
}

void mainGame::Render()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	SCENEMANAGER->Render(sprite);

	sprite->End();
}

void mainGame::LostDevice()
{
}

void mainGame::ResetDevice()
{
}
