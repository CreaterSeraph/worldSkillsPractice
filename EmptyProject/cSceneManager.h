#pragma once
#include "singleton.h"

class cScene;
class cSceneManager : public singleton<cSceneManager>
{
private:
	weak_ptr<cScene> nowScene;
	weak_ptr<cScene> nextScene;
	map<string, shared_ptr<cScene>> m_sceneMap;
public:
	cSceneManager();
	~cSceneManager();

	weak_ptr<cScene> AddScene(string_view key, shared_ptr<cScene> scene);
	weak_ptr<cScene> ChangeScene(string_view key);
	weak_ptr<cScene> FindScene(string_view key);
	
	void Release();
	void Update(double dt);
	void Render(LPD3DXSPRITE sprite);
};

#define SCENEMANAGER cSceneManager::Get()