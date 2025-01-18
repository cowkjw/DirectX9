#pragma once
#include "Define.h"

class CUiManager
{
private:
	CUiManager();
	~CUiManager();
public:
	void Render(HDC hDC);
	void Set_UiType(UITYPE _type) { m_eCurUi = _type; }
public:
	static CUiManager* Get_Instance()
	{
		if (nullptr == m_pInstance) {
			m_pInstance = new CUiManager;
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
	void RenderUi_YG(HDC hDC);
	void RenderUi_CY(HDC hDC);
	void RenderUi_DW(HDC hDC);
	void RenderUi_JW(HDC hDC);

private:
	static CUiManager* m_pInstance;
	UITYPE m_eCurUi;
};

