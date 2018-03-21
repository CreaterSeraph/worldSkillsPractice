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
	, backGround(new texture("./image/map.png"))
{
}


mainScene::~mainScene()
{
}

void mainScene::Init()
{
	D3DLOCKED_RECT LockRect;

	backGround->m_texturePtr->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);

	DWORD* pColor = (DWORD*)LockRect.pBits; // 잠금후 픽셀 값 받아오기

	for (int i = 0; i < backGround->m_info.Height; i++)
	{
		for (int j = 0; j < backGround->m_info.Width; j++)
		{
			int idx = i * backGround->m_info.Width + j;

			pColor[idx] = pColor[idx] & 0xffff00ff;
		}
	}
	backGround->m_texturePtr->UnlockRect(0);
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
	backGround->Render(sprite, WINSIZEX / 2, 0);

	btExit->Render(sprite);
	btHow->Render(sprite);
	btStart->Render(sprite);
}
