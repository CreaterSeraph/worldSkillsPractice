#include "DXUT.h"
#include "cImageManager.h"


cImageManager::cImageManager()
{
}


cImageManager::~cImageManager()
{
}

shared_ptr<texture> cImageManager::FindTexture(string_view path)
{
	auto& find = m_textureMap.find(path.data());
	if (find == m_textureMap.end()) return shared_ptr<texture>();

	return find->second;
}

shared_ptr<texture> cImageManager::AddTexture(string_view path, const sTextureData& data)
{
	auto& result = m_textureMap[path.data()];
	if (!result)
		result = shared_ptr<texture>(new texture(path, data));

	return result;
}
