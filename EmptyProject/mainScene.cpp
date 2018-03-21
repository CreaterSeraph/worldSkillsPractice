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
	btExit->Render(sprite);
	btHow->Render(sprite);
	btStart->Render(sprite);
}
