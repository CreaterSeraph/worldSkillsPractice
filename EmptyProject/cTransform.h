#pragma once
struct cTransform
{
	D3DXVECTOR2				m_pos;
	optional<double>		m_rot;
	optional<D3DXVECTOR2>	m_scale;
	D3DCOLOR				m_color;

	cTransform(D3DXVECTOR2 pos, D3DCOLOR color = 0xffffffff, optional<double> rot = optional<double>(), optional<D3DXVECTOR2> scale = optional<D3DXVECTOR2>());
	~cTransform();

	D3DXMATRIX GetMatrix() const;
};