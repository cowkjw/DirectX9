#include "pch.h"
#include "CSceneManager.h"
#include "CMenuScene.h"
#include "CYGScene.h"
#include "CCYScene.h"
#include "CDWScene.h"
#include "CJWScene.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

CSceneManager::CSceneManager() : m_pScene(nullptr), m_eCurScene(SC_MENU), m_ePreScene(SC_END)
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::Set_Scene(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_MENU:
			m_pScene = new CMenuScene;
			break;
		case SC_YG:
			m_pScene = new CYGScene;
			break;
		case SC_CY:
			m_pScene = new CCYScene;
			break;
		case SC_DW:
			m_pScene = new CDWScene;
			break;
		case SC_JW:
			m_pScene = new CJWScene;
			break;
		case SC_END:
			break;
		default:
			break;
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

int CSceneManager::Update()
{
	m_pScene->Update();
	return 0;
}

void CSceneManager::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneManager::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneManager::Release()
{
	Safe_Delete(m_pScene);
}
