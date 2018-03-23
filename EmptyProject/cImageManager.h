#pragma once
#include "singleton.h"

class cImageManager : public singleton<cImageManager>
{
private:
	map<string, shared_ptr<texture>> m_textureMap;
public:
	cImageManager();
	~cImageManager();

	shared_ptr<texture> FindTexture(string_view path);
	shared_ptr<texture> AddTexture(string_view path, const sTextureData& data = sTextureData());
};

#define IMAGEMANAGER cImageManager::Get()
