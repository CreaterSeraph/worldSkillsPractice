#pragma once
class tileAdmin
{
private:
	int tileState[100];


public:
	tileAdmin();
	~tileAdmin();

	void Render();
};

class unitObj
{
	size_t objName;
	POINT startPos;
	enum UNITDIR
	{
		UD_U, UD_RU, UD_RD, UD_D, UD_LD, UD_LU
	} dir;

	int GetLen()
	{
		return *("" + objName) - 'a';
	}
};