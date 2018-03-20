#include "DXUT.h"
#include "cTransform.h"


cTransform::cTransform(D3DXVECTOR2 pos, D3DCOLOR color, optional<double> rot, optional<D3DXVECTOR2> scale)
	:m_pos(pos), m_color(color), m_rot(rot), m_scale(scale)
{
}

cTransform::~cTransform()
{
}

D3DXMATRIX cTransform::GetMatrix() const
{
	D3DXMATRIX result;

	D3DXMatrixIdentity(&result);

	if (m_scale)
	{
		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, m_scale.value().x, m_scale.value().y, 1);

		result *= matS;
	}

	if (m_rot)
	{
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationZ(&matR, m_rot.value());

		result *= matR;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, 0);

	result *= matT;

	return result;
}
