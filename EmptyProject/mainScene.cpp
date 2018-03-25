#include "DXUT.h"
#include "mainScene.h"

#include "cButton.h"

mainScene::mainScene()
	:btExit(new cButton("./image/ui_exit_1.png", "./image/ui_exit_2.png",
		[]() {PostQuitMessage(0); },
		D3DXVECTOR2(WINSIZEX / 2 + 300, WINSIZEY - 160)))
	, btHow(new cButton("./image/ui_how_1.png", "./image/ui_how_2.png",
		[]() { },
		D3DXVECTOR2(WINSIZEX / 2 - 300, WINSIZEY - 160)))
	, btStart(new cButton("./image/ui_start_1.png", "./image/ui_start_2.png",
		[]() {SCENEMANAGER->ChangeScene("ready"); },
		D3DXVECTOR2(WINSIZEX / 2, WINSIZEY - 160)))
	, backGround(IMAGEMANAGER->AddTexture("./image/main_background.png", sTextureData(D3DXVECTOR2(0, 0))))
	, backGroundani(IMAGEMANAGER->AddTexture("./image/main_battleship.png", sTextureData(D3DXVECTOR2(0, 0))))
{
}


mainScene::~mainScene()
{
}

void mainScene::Init()
{
}

void mainScene::Release()
{
}

void mainScene::Update(double dt)
{
	btExit->Update();
	btHow->Update();
	btStart->Update();
}

void mainScene::Render(LPD3DXSPRITE sprite)
{
	backGround->Render(sprite, 0, 0);
	backGroundani->Render(sprite, 0, sin(DXUTGetTime() * 3) * 40 + 40);

	btExit->Render(sprite);
	btHow->Render(sprite);
	btStart->Render(sprite);
}
