#include "pch.h"
#include "CCYScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CObjectManager.h"
#include "CUiManager.h"
#include "CAbstractFactory.h"
#include "CCYPlayer.h"

CCYScene::CCYScene()
{
}

void CCYScene::Initialize()
{
	CObjectManager::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CCYPlayer>::Create(300, 400, 100, 100));
	CUiManager::Get_Instance()->Set_UiType(UI_CY);
}

int CCYScene::Update()
{
	Key_Input();
	CObjectManager::Get_Instance()->Update();
    return 0;
}

void CCYScene::Late_Update()
{
	CObjectManager::Get_Instance()->Late_Update();
}

void CCYScene::Render(HDC hDC)
{
	Rectangle(hDC, -100, -100, 900, 700);

	CObjectManager::Get_Instance()->Render(hDC);
	if (g_bDevmode) {
		TCHAR szWhoScene[64];
		_stprintf_s(szWhoScene, _T("Ã¤¿µ"));
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, 300, 10, szWhoScene, _tcslen(szWhoScene));
	}
}

void CCYScene::Release()
{
	CObjectManager::Get_Instance()->Delete_ALL();
	CObjectManager::Get_Instance()->RenderList_Clear();
}

void CCYScene::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
		g_bDevmode = !g_bDevmode;
	}

	if (CKeyManager::Get_Instance()->Key_Down(VK_F9)) {
		CSceneManager::Get_Instance()->Set_Scene(SC_MENU);
	}
}

void CCYScene::Create_MapObj()
{
}

void CCYScene::Offset()
{
}
