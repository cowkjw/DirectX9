#include "pch.h"
#include "CObjectManager.h"
CObjectManager* CObjectManager::m_pInstance = nullptr;

CObjectManager::CObjectManager()
{
}

void CObjectManager::Add_Object(OBJID eID, CObject* pObj)
{
	if (OBJ_END <= eID || nullptr == pObj || eID < OBJ_PLAYER)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjectManager::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObject*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return 0;
}

void CObjectManager::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID	eID = pObj->Get_GroupID();
			m_RenderList[eID].push_back(pObj);
		}
	}
}

void CObjectManager::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObject* pDst, CObject* pSrc)->bool
			{
				return pDst->Get_Info().vPos.y< pSrc->Get_Info().vPos.y;
			});

		for (auto& pObj : m_RenderList[i])
			pObj->Render(hDC);

		m_RenderList[i].clear();
	}
}

void CObjectManager::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObject*>);
		m_ObjList[i].clear();
	}
}

void CObjectManager::Delete_ID(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
		Safe_Delete(pObj);

	m_ObjList[eID].clear();
}

void CObjectManager::Delete_ALL()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObject*>);
		m_ObjList[i].clear();
	}

}

void CObjectManager::RenderList_Clear()
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].clear();
	}
}
