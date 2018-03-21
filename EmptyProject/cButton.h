#pragma once
class cButton
{
private:
	shared_ptr<texture> normal;
	shared_ptr<texture> click;

	function<void()> func;

	enum BUTTON_STATE
	{
		BTST_NORMAL, BTST_OVER, BTST_CLICK, BTST_OUTCLICK
	} state;

	RECT rc;
	D3DXVECTOR2 pos;
public:
	cButton(const string& normalPath, const string& clickPath, function<void()> func, const D3DXVECTOR2& pos);
	~cButton();

	void Update();
	void Render(LPD3DXSPRITE sprite);
};

