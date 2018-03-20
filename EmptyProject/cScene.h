#pragma once
class cScene abstract
{
protected:
	double m_camScale;
	D3DXVECTOR2 m_camPos;

	D3DXMATRIX GetCamMaxtrix();
public:
	cScene();
	virtual ~cScene();

	virtual void Init() {}
	virtual void Release() {}
	virtual void Update(double dt) {}
	virtual void Render(LPD3DXSPRITE sprite) {}
};

