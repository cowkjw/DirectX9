#pragma once
#include "Define.h"
#include "CScene.h"

class CSceneManager
{
private:
	CSceneManager();
	~CSceneManager() { Release(); }
public:
	void		Set_Scene(SCENEID eID);
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	SCENEID Get_SceneID() { return m_eCurScene; }
	CScene* Get_Scene() { return m_pScene; }
public:
	static CSceneManager* Get_Instance()
	{
		if (nullptr == m_pInstance) {
			m_pInstance = new CSceneManager;
		}

		return m_pInstance;
	}

	static void Destroy_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CSceneManager* m_pInstance;
	CScene* m_pScene;

	SCENEID				m_eCurScene;
	SCENEID				m_ePreScene;
};

