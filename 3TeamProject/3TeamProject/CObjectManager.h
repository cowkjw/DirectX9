#pragma once
#include "CObject.h"
class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager() { Release(); }
public:
	void		Add_Object(OBJID eID, CObject* pObj);
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	void		Delete_ID(OBJID eID);
	void		Delete_ALL();
	void		RenderList_Clear();
public: //JW
	auto& Get_ObjList_ByID(OBJID eID) { return m_ObjList[eID]; }
public:
	static CObjectManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjectManager;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CObjectManager* m_pInstance;
	list<CObject*>		m_ObjList[OBJ_END];
	list<CObject*>		m_RenderList[RENDER_END];
};

