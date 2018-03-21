#pragma once
class font
{
private:
	LPD3DXFONT fontPtr;
	D3DXMATRIX mat;
public:
	font(const string& path, size_t height = 30);
	~font();

	void SetMatrix(const D3DXMATRIX& mat) { this->mat = mat; }
	void SetBasicMatrix();
	void Print(LPD3DXSPRITE sprite, float x, float y, const string& text, DWORD color = 0xffffffff);
};

