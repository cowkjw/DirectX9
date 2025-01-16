#include "pch.h"
#include "CUiManager.h"

CUiManager::CUiManager():m_eCurUi(UI_END)
{
}

CUiManager::~CUiManager()
{
}

void CUiManager::Render(HDC hDC)
{
	switch (m_eCurUi)
	{
	case UI_YG:
		RenderUi_YG(hDC);
		break;
	case UI_CY:
		RenderUi_CY(hDC);
		break;
	case UI_DH:
		RenderUi_DH(hDC);
		break;
	case UI_JW:
		RenderUi_JW(hDC);
		break;
	case UI_END:
		break;
	default:
		break;
	}
}

void CUiManager::RenderUi_YG(HDC hDC)
{
}

void CUiManager::RenderUi_CY(HDC hDC)
{
}

void CUiManager::RenderUi_DH(HDC hDC)
{
}

void CUiManager::RenderUi_JW(HDC hDC)
{
}