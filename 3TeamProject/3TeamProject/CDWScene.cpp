#include "pch.h"
#include "CDWScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"

CDWScene::CDWScene()
{
}

void CDWScene::Initialize()
{
}

int CDWScene::Update()
{
	Key_Input();
    return 0;
}

void CDWScene::Late_Update()
{
}

void CDWScene::Render(HDC hDC)
{
	Rectangle(hDC, -100, -100, 900, 700);

	if (g_bDevmode) {
		TCHAR szWhoScene[64];
		_stprintf_s(szWhoScene, _T("µ¿¿Ï"));
		SetTextColor(hDC, RGB(0, 0, 0));
		//SetBkMode(hDC, TRANSPARENT);
		TextOut(hDC, 300, 10, szWhoScene, _tcslen(szWhoScene));
	}
}

void CDWScene::Release()
{
}

void CDWScene::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
		g_bDevmode = !g_bDevmode;
	}

	if (CKeyManager::Get_Instance()->Key_Down(VK_F9)) {
		CSceneManager::Get_Instance()->Set_Scene(SC_MENU);
	}
}

void CDWScene::Create_MapObj()
{
}

void CDWScene::Offset()
{
}
