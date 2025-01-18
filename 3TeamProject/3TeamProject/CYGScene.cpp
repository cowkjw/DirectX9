#include "pch.h"
#include "CYGScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CUiManager.h"
#include "CYGPlayer.h"
#include "CYGBox.h"
#include "CScrollManager.h"

CYGScene::CYGScene()
{
}

void CYGScene::Initialize()
{
	CScrollManager::Get_Instance()->Set_ScrollLock(4000, 4000);
	CObjectManager::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CYGPlayer>::Create(400, 300, 50, 50));
	CUiManager::Get_Instance()->Set_UiType(UI_YG);

	Create_MapObj();
}

int CYGScene::Update()
{
	Key_Input();
	CObjectManager::Get_Instance()->Update();
	Offset();
    return 0;
}

void CYGScene::Late_Update()
{
	CObjectManager::Get_Instance()->Late_Update();
}

void CYGScene::Render(HDC hDC)
{
	COLORREF color = RGB(128, 175, 73);

	HBRUSH hBrush = CreateSolidBrush(color);
	HPEN hPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	Rectangle(hDC, -2000, -2000, 2000, 2000);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	

	CObjectManager::Get_Instance()->Render(hDC);
	CUiManager::Get_Instance()->Render(hDC);

	if (g_bDevmode) {
		TCHAR szWhoScene[64];
		_stprintf_s(szWhoScene, _T("À¯°æ"));
		SetTextColor(hDC, RGB(0, 0, 0));
		//SetBkMode(hDC, TRANSPARENT);
		TextOut(hDC, 300, 10, szWhoScene, _tcslen(szWhoScene));
	}

}

void CYGScene::Release()
{
	CObjectManager::Get_Instance()->Delete_ALL();
	CObjectManager::Get_Instance()->RenderList_Clear();
}

void CYGScene::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
		g_bDevmode = !g_bDevmode;
	}

	if (CKeyManager::Get_Instance()->Key_Down(VK_F9)) {
		CSceneManager::Get_Instance()->Set_Scene(SC_MENU);
	}
}

void CYGScene::Create_MapObj()
{
	CObjectManager::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CYGBox>::Create(300, 300, 70, 70));
}

void CYGScene::Offset()
{
	CObject* _copyPlayer = CObjectManager::Get_Instance()->Get_Player();
	int		iOffSetminX = 412;
	int		iOffSetmaxX = 612;

	int iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
	if (iOffSetminX > _copyPlayer->Get_Info().vPos.x+ iScrollX)
		CScrollManager::Get_Instance()->Set_ScrollX(_copyPlayer->Get_Speed());

	if (iOffSetmaxX < _copyPlayer->Get_Info().vPos.x + iScrollX)
		CScrollManager::Get_Instance()->Set_ScrollX(-_copyPlayer->Get_Speed());

	int		iOffSetminY = 260;
	int		iOffSetmaxY = 460;

	int		iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

	if (iOffSetminY > _copyPlayer->Get_Info().vPos.y + iScrollY)
		CScrollManager::Get_Instance()->Set_ScrollY(_copyPlayer->Get_Speed());

	if (iOffSetmaxY < _copyPlayer->Get_Info().vPos.y + iScrollY)
		CScrollManager::Get_Instance()->Set_ScrollY(-_copyPlayer->Get_Speed());
}
