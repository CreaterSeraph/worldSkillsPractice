#include "DXUT.h"
#include "cScene.h"


D3DXMATRIX cScene::GetCamMaxtrix()
{
	D3DXMATRIX matS, matT;

	D3DXMatrixScaling(&matS, m_camScale, m_camScale, m_camScale);
	D3DXMatrixTranslation(&matT, m_camPos.x, m_camPos.y, 0);

	return matS * matT;
}

cScene::cScene()
	:m_camScale(1), m_camPos(0, 0)
{
}


cScene::~cScene()
{
}
