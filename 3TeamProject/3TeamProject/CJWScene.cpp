#include "pch.h"
#include "CJWScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"

CJWScene::CJWScene()
{
}

void CJWScene::Initialize()
{
}

int CJWScene::Update()
{
	Key_Input();
    return 0;
}

void CJWScene::Late_Update()
{
}

void CJWScene::Render(HDC hDC)
{
	Rectangle(hDC, -100, -100, 900, 700);

	if (g_bDevmode) {
		TCHAR szWhoScene[64];
		_stprintf_s(szWhoScene, _T("Àå¿ø"));
		SetTextColor(hDC, RGB(0, 0, 0));
		//SetBkMode(hDC, TRANSPARENT);
		TextOut(hDC, 300, 10, szWhoScene, _tcslen(szWhoScene));
	}
}

void CJWScene::Release()
{
}

void CJWScene::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
		g_bDevmode = !g_bDevmode;
	}

	if (CKeyManager::Get_Instance()->Key_Down(VK_F9)) {
		CSceneManager::Get_Instance()->Set_Scene(SC_MENU);
	}
}

void CJWScene::Create_MapObj()
{
}

void CJWScene::Offset()
{
}
