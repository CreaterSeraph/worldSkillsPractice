#include "DXUT.h"
#include "cScene.h"


D3DXMATRIX cScene::GetCamMatrix()
{
	D3DXMATRIX matS, matT, matP;
	D3DXMatrixScaling(&matS, m_cam.scale, m_cam.scale, m_cam.scale);
	D3DXMatrixTranslation(&matT, WINSIZEX / 2 - WINSIZEX / 2 * m_cam.scale, WINSIZEY / 2 - WINSIZEY / 2 * m_cam.scale, 0);

	D3DXMatrixTranslation(&matP, WINSIZEX / 2 - m_cam.pos.x, WINSIZEY / 2 - m_cam.pos.y, 0);

	return matP * matS * matT;
}

cScene::cScene()
	:m_cam()
{
}


cScene::~cScene()
{
}