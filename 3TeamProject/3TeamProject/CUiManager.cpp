#include "pch.h"
#include "CUiManager.h"
#include "CObjectManager.h"
#include "CYGPlayer.h"

CUiManager* CUiManager::m_pInstance = nullptr;

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
	case UI_DW:
		RenderUi_DW(hDC);
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
	CYGPlayer* _copyYGPlayer = static_cast<CYGPlayer*>(CObjectManager::Get_Instance()->Get_Player());
	int hpWidth = (400 * _copyYGPlayer->Get_Hp()) / _copyYGPlayer->Get_MaxHp();

	COLORREF color = RGB(179, 179, 179);
	HBRUSH hBrush = CreateSolidBrush(color);
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, WINCX/2-200,510, WINCX / 2 - 200 + hpWidth, 550, 10, 10);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void CUiManager::RenderUi_CY(HDC hDC)
{
}

void CUiManager::RenderUi_DW(HDC hDC)
{
}

void CUiManager::RenderUi_JW(HDC hDC)
{
}