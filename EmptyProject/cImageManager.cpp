#include "DXUT.h"
#include "cImageManager.h"


cImageManager::cImageManager()
{
}


cImageManager::~cImageManager()
{
}

shared_ptr<texture> cImageManager::FindTexture(const string& path)
{
	auto& find = m_textureMap.find(path);
	if (find == m_textureMap.end()) return shared_ptr<texture>();

	return find->second;
}

shared_ptr<texture> cImageManager::AddTexture(const string& path, const sTextureData& data)
{
	auto& result = m_textureMap[path];
	if (!result)
		result = shared_ptr<texture>(new texture(path, data));

	return result;
}
