#pragma once

//typedef pair<D3DXVECTOR2, double> CamData;
struct CamData
{
	double scale;
	D3DXVECTOR2 pos;

	CamData()
		:pos(WINSIZEX / 2, WINSIZEY / 2), scale(1)
	{
	}

	CamData(const D3DXVECTOR2& pos, double scale = 1)
		:pos(pos), scale(scale)
	{
	}
};


class cScene abstract
{
protected:
	CamData m_cam;

	D3DXMATRIX GetCamMaxtrix();
public:
	cScene();
	virtual ~cScene();

	virtual void Init() {}
	virtual void Release() {}
	virtual void Update(double dt) {}
	virtual void Render(LPD3DXSPRITE sprite) {}
};

