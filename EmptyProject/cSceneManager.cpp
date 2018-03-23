#include "DXUT.h"
#include "cSceneManager.h"
#include "cScene.h"


cSceneManager::cSceneManager()
	:nowScene(), nextScene()
{
}


cSceneManager::~cSceneManager()
{
}


void cSceneManager::Release()
{
	if(!nowScene.expired())
		nowScene.lock()->Release();
	m_sceneMap.clear();
}

void cSceneManager::Update(double dt)
{
	if (!nextScene.expired())
	{
		if (!nowScene.expired())
			nowScene.lock()->Release();
		nowScene = nextScene;
		nextScene.reset();
		nowScene.lock()->Init();
	}
	if (!nowScene.expired())
		nowScene.lock()->Update(dt);
}

void cSceneManager::Render(LPD3DXSPRITE sprite)
{
	if (!nowScene.expired())
		nowScene.lock()->Render(sprite);
}

weak_ptr<cScene> cSceneManager::AddScene(string_view key, shared_ptr<cScene> scene)
{
	auto find = m_sceneMap.find(key.data());
	if (find != m_sceneMap.end()) return weak_ptr<cScene>();

	auto& [insertPos, value] = m_sceneMap.insert(make_pair(key, scene));
	//auto& result = m_sceneMap.insert(make_pair(key, scene));
	return weak_ptr<cScene>((*insertPos).second);
}

weak_ptr<cScene> cSceneManager::ChangeScene(string_view key)
{
	auto& find = m_sceneMap.find(key.data());
	if (find == m_sceneMap.end()) return weak_ptr<cScene>();

	nextScene = find->second;
	return nextScene;
}

weak_ptr<cScene> cSceneManager::FindScene(string_view key)
{
	auto& find = m_sceneMap.find(key.data());
	if (find == m_sceneMap.end()) return weak_ptr<cScene>();

	return find->second;
}
