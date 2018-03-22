#include "DXUT.h"
#include "font.h"


font::font(string_view path, size_t height)
{
	HRESULT hr;
	hr = D3DXCreateFontA(Device, height, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, 0, 0, FF_DONTCARE, path.data(), &fontPtr);
	if (FAILED(hr))
	{
		DEBUG_LOG("�� ��Ʈ�� �̰� �ƴѰ���" << path);
	}
	D3DXMatrixIdentity(&mat);
}


font::~font()
{
	SAFE_RELEASE(fontPtr);
}

void font::SetBasicMatrix()
{
	D3DXMatrixIdentity(&mat);
}

void font::Print(LPD3DXSPRITE sprite, float x, float y, string_view text, DWORD color)
{
	sprite->SetTransform(&mat);

	fontPtr->DrawTextA(sprite, text.data(), -1, nullptr, DT_NOCLIP, color);
}
