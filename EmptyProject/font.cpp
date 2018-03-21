#include "DXUT.h"
#include "font.h"


font::font(const string& path, size_t height)
{
	HRESULT hr;
	hr = D3DXCreateFontA(Device, height, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, 0, 0, FF_DONTCARE, path.c_str(), &fontPtr);
	if (FAILED(hr))
	{
		DEBUG_LOG("어 폰트가 이게 아닌가봐" << path.c_str());
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

void font::Print(LPD3DXSPRITE sprite, float x, float y, const string& text, DWORD color)
{
	sprite->SetTransform(&mat);

	fontPtr->DrawTextA(sprite, text.c_str(), -1, nullptr, DT_NOCLIP, color);
}
