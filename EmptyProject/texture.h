#pragma once

struct MYIMAGEINFO : public D3DXIMAGE_INFO
{
	MYIMAGEINFO()
	{
		ZeroMemory(this, sizeof(MYIMAGEINFO));
		this->Width = D3DX_DEFAULT_NONPOW2;
		this->Height = D3DX_DEFAULT_NONPOW2;
	}
};

struct sTextureData
{
	D3DXVECTOR2 offset;
	D3DXVECTOR2 pos;

	sTextureData(const D3DXVECTOR2& offset = D3DXVECTOR2(0.5, 0.5), const D3DXVECTOR2& pos = D3DXVECTOR2(0, 0))
		:offset(offset), pos(pos)
	{
	}
	~sTextureData() {}
};

struct texture
{
	static D3DXMATRIX GetIdentityMatrix()
	{
		D3DXMATRIX result;
		D3DXMatrixIdentity(&result);

		return result;
	}

	LPDIRECT3DTEXTURE9 m_texturePtr;
	MYIMAGEINFO m_info;
	D3DXVECTOR3 m_center;
	D3DXVECTOR3 m_pos;

	texture(const string& path, const sTextureData& loadData = sTextureData());
	~texture();

	void Render(LPD3DXSPRITE sprite, const cTransform& transform, const D3DXMATRIX& camMatrix = GetIdentityMatrix(), const RECT* rc = nullptr);
	void Render(LPD3DXSPRITE sprite, float x, float y, const D3DXMATRIX& camMatrix = GetIdentityMatrix());
	void Render(LPD3DXSPRITE sprite, const D3DXVECTOR2& pos, const D3DXMATRIX& camMatrix = GetIdentityMatrix());
	void Render(LPD3DXSPRITE sprite, DWORD color, const D3DXVECTOR2& pos, const D3DXMATRIX& camMatrix = GetIdentityMatrix());
};

