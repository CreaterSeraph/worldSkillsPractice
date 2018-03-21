#include "DXUT.h"
#include "cScene.h"


D3DXMATRIX cScene::GetCamMaxtrix()
{
	//D3DXMATRIX matTemp;
	//D3DXMatrixScaling(&matTemp, 1 / m_camScale, 1 / m_camScale, 1 / m_camScale);
	//D3DXVECTOR2 camStartPos = m_camPos;
	//D3DXVec2TransformNormal(&camStartPos, &camStartPos, &matTemp);

	D3DXMATRIX matS, matT, matP;
	D3DXMatrixScaling(&matS, m_cam.scale, m_cam.scale, m_cam.scale);
	D3DXMatrixTranslation(&matT, WINSIZEX / 2 - WINSIZEX / 2 * m_cam.scale, WINSIZEY / 2 - WINSIZEY / 2 * m_cam.scale, 0);

	D3DXMatrixTranslation(&matP, m_cam.pos.x - WINSIZEX / 2, -(m_cam.pos.y - WINSIZEY / 2), 0);

	return matP * matS * matT;
}

cScene::cScene()
	:m_cam(D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2), 1)
{
}


cScene::~cScene()
{
}
