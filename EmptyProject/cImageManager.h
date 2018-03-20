#pragma once
#include "singleton.h"

class cImageManager : public singleton<cImageManager>
{
private:
	map<string, shared_ptr<texture>> m_textureMap;
public:
	cImageManager();
	~cImageManager();

	shared_ptr<texture> FindTexture(const string& path);
	shared_ptr<texture> AddTexture(const string& path, const sTextureData& data = sTextureData());
};

#define IMAGEMANAGER cImageManager::Get()
