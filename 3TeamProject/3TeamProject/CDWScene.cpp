#include "pch.h"
#include "CDWScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CObjectManager.h"
#include "CUiManager.h"
#include "CAbstractFactory.h"
#include "CDWPlayer.h"

CDWScene::CDWScene()
{
}

void CDWScene::Initialize()
{
	CObjectManager::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CDWPlayer>::Create(300, 400, 100, 100));
	CUiManager::Get_Instance()->Set_UiType(UI_DW);
}

int CDWScene::Update()
{
	Key_Input();
	CObjectManager::Get_Instance()->Update();
    return 0;
}

void CDWScene::Late_Update()
{
	CObjectManager::Get_Instance()->Late_Update();
}

void CDWScene::Render(HDC hDC)
{
	Rectangle(hDC, -100, -100, 900, 700);

	CObjectManager::Get_Instance()->Render(hDC);
	if (g_bDevmode) {
		TCHAR szWhoScene[64];
		_stprintf_s(szWhoScene, _T("µ¿¿Ï"));
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, 300, 10, szWhoScene, _tcslen(szWhoScene));
	}
}

void CDWScene::Release()
{
	CObjectManager::Get_Instance()->Delete_ALL();
	CObjectManager::Get_Instance()->RenderList_Clear();
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
