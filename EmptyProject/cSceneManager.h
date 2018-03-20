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

	weak_ptr<cScene> AddScene(const string& key, shared_ptr<cScene> scene);
	weak_ptr<cScene> ChangeScene(const string& key);
	
	void Release();
	void Update(double dt);
	void Render(LPD3DXSPRITE sprite);
};

#define SCENEMANAGER cSceneManager::Get()