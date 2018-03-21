#include "DXUT.h"
#include "texture.h"

texture::texture(const string& path, const sTextureData& loadData)
	:m_center(0, 0, 0), m_pos(0, 0, 0), m_info(), m_texturePtr(nullptr)
{
	HRESULT hr;

	hr = D3DXCreateTextureFromFileExA(Device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &m_info, nullptr, &m_texturePtr);

	if (FAILED(hr))
	{
		DEBUG_LOG("로딩실패!" << path.c_str());
	}

	m_center.x = m_info.Width * loadData.offset.x;
	m_center.y = m_info.Height * loadData.offset.y;

	m_pos.x = loadData.pos.x;
	m_pos.y = loadData.pos.y;
}

texture::~texture()
{
	SAFE_RELEASE(m_texturePtr);
}

void texture::Render(LPD3DXSPRITE sprite, const cTransform& transform, const D3DXMATRIX& camMatrix, const RECT* rc)
{
	sprite->SetTransform(&(transform.GetMatrix() * camMatrix));
	sprite->Draw(m_texturePtr, rc, &m_center, &m_pos, transform.m_color);
}

void texture::Render(LPD3DXSPRITE sprite, float x, float y, const D3DXMATRIX& camMatrix)
{
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, x, y, 0);
	sprite->SetTransform(&(matT * camMatrix));
	sprite->Draw(m_texturePtr, nullptr, &m_center, &m_pos, 0xffffffff);
}

void texture::Render(LPD3DXSPRITE sprite, const D3DXVECTOR2& pos, const D3DXMATRIX& camMatrix)
{
	Render(sprite, pos.x, pos.y, camMatrix);
}
