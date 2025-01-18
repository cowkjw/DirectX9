#include "pch.h"
#include "CCYScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CObjectManager.h"
#include "CUiManager.h"
#include "CAbstractFactory.h"
#include "CCYPlayer.h"
#include "CCYFood.h"
#include "CCollisionManager.h"
#include "CCYMonster.h"


CCYScene::CCYScene() : m_ullFoodTimeTicker(0)
{
}

void CCYScene::Initialize()
{
	CObjectManager::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CCYPlayer>::Create(300, 400, 35, 35));
	//m_SlitherSegvec.push_back(static_cast<CCYPlayer*>(OBJMGR->Get_ObjList_ByID(OBJ_PLAYER).front())->Get_)
	CUiManager::Get_Instance()->Set_UiType(UI_CY);
}

int CCYScene::Update()
{
	Key_Input();
	CCollisionManager::Collision_Circle(OBJMGR->Get_ObjList_ByID(OBJ_PLAYER), OBJMGR->Get_ObjList_ByID(OBJ_MISC));
	if (m_ullFoodTimeTicker + rand() % 20 * 20  + 1000 < GetTickCount64())
	{
		CObjectManager::Get_Instance()->Add_Object(OBJ_MISC, CAbstractFactory<CCYFood>::Create());
		m_ullFoodTimeTicker = GetTickCount64();
	}

	CObjectManager::Get_Instance()->Update();
    return 0;
}

void CCYScene::Late_Update()
{
	//CCollisionManager::Collision_Circle(OBJMGR->Get_ObjList_ByID(OBJ_PLAYER), OBJMGR->Get_ObjList_ByID(OBJ_CYTAIL));
	//CCollisionManager::Collision_Circle(OBJMGR->Get_ObjList_ByID(OBJ_MONSTER), OBJMGR->Get_ObjList_ByID(OBJ_CYTAIL));
	CObjectManager::Get_Instance()->Late_Update();
}

void CCYScene::Render(HDC hDC)
{
	//RGB(13, 21, 32)
	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(20, 29, 43));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);


	HBRUSH PinkBrush = CreateSolidBrush(RGB(20, 29, 43));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, PinkBrush);

	Rectangle(hDC, -100, -100, 900, 700);

	SelectObject(hDC, OldBrush); DeleteObject(PinkBrush);
	SelectObject(hDC, hOldPen); DeleteObject(hPen);

	CObjectManager::Get_Instance()->Render(hDC);
	if (g_bDevmode) {
		TCHAR szWhoScene[64];
		_stprintf_s(szWhoScene, _T("Ã¤¿µ"));
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, 300, 10, szWhoScene, _tcslen(szWhoScene));
	}
	CUiManager::Get_Instance()->Render(hDC);
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

	if (CKeyManager::Get_Instance()->Key_Down('1'))
	{
		CObjectManager::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCYMonster>::Create());

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
