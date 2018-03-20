#include "DXUT.h"
#include "mainGame.h"
#include "mainScene.h"
#include "gameScene.h"
#include "readyScene.h"

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
	auto ingame = SCENEMANAGER->AddScene("game", shared_ptr<cScene>(new gameScene));
	auto castedGameScene = static_pointer_cast<gameScene>(ingame.lock());
	SCENEMANAGER->AddScene("ready", shared_ptr<cScene>(new readyScene(castedGameScene)));
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
	sprite->OnLostDevice();
}

void mainGame::ResetDevice()
{
	sprite->OnResetDevice();
}
