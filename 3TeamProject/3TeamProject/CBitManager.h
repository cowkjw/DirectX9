#pragma once
#include "CMyBmp.h"
class CBitManager
{
private:
	CBitManager();
	~CBitManager();

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Image(const TCHAR* pImgKey);
	void		Release();

public:
	static CBitManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBitManager;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


private:
	static CBitManager* m_pInstance;

	map<const TCHAR*, CMyBmp*>	m_mapBit;

};

