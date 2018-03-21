#include "DXUT.h"
#include "cButton.h"

cButton::cButton(const string& normalPath, const string& clickPath, function<void()> func, const D3DXVECTOR2& pos)
	:func(func), normal(IMAGEMANAGER->AddTexture(normalPath)), click(IMAGEMANAGER->AddTexture(clickPath)), state(BTST_NORMAL), pos(pos)
{
	rc.left = pos.x - normal->m_info.Width / 2;
	rc.top = pos.y - normal->m_info.Height / 2;
	rc.right = pos.x + normal->m_info.Width / 2;
	rc.bottom = pos.y + normal->m_info.Height / 2;
}

cButton::~cButton()
{
}

void cButton::Update()
{
	bool collide = PtInRect(&rc, ptMouse);
	bool isClick = KEYMANAGER->IsOnceKeyDown(VK_LBUTTON);
	switch (state)
	{
	case cButton::BTST_NORMAL:
		if (collide)
			state = BTST_OVER;

		break;
	case cButton::BTST_OVER:
		if (!collide)
			state = BTST_NORMAL;
		if (isClick)
			state = BTST_CLICK;

		break;
	case cButton::BTST_CLICK:
		if (!collide)
			state = BTST_OUTCLICK;
		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
		{
			func();
			state = BTST_NORMAL;
		}

		break;
	case cButton::BTST_OUTCLICK:
		if (collide)
			state = BTST_CLICK;
		if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
			state = BTST_NORMAL;

		break;
	}
}

void cButton::Render(LPD3DXSPRITE sprite)
{
	if (state != BTST_CLICK)
		normal->Render(sprite, pos.x, pos.y);
	else
		click->Render(sprite, pos.x, pos.y);
}
