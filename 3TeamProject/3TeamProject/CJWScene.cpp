#include "pch.h"
#include "CJWScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CUiManager.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"

CJWScene::CJWScene() :m_pFruit(nullptr), m_iLevel(1), m_bCreated(false),
m_dwDropDelay(0ULL), m_dwDroppedTime(0ULL)
{
	for (int i = 0; i < (int)FRUIT_TYPE::END; i++)
	{
		m_FruitPoolMap[(FRUIT_TYPE)i] = nullptr;
	}
}

void CJWScene::Initialize()
{
	m_dwDropDelay = 1500ULL;
	m_dwDroppedTime = GetTickCount64();
	m_bCreated = true;
	m_iLevel = 1;
	for (int i = 0; i < (int)FRUIT_TYPE::END; i++)
	{
		if (!m_FruitPoolMap[(FRUIT_TYPE)i])
		{
			m_FruitPoolMap[(FRUIT_TYPE)i] = new CObjPool<CFruit>(20);
		}
	}
	CObjectManager::Get_Instance()->Add_Object(OBJ_PLAYER, m_FruitPoolMap[FRUIT_TYPE::ORANGE]->Get_Obj());

	CUiManager::Get_Instance()->Set_UiType(UI_JW);
}

int CJWScene::Update()
{
	auto& fruitList = CObjectManager::Get_Instance()->Get_ObjList_ByID(OBJ_PLAYER);
	CCollisionManager::JW_Collision_Circle(fruitList, fruitList);
	Create_MapObj();
	CObjectManager::Get_Instance()->Update();

	Key_Input();
	return 0;
}

void CJWScene::Late_Update()
{
	CObjectManager::Get_Instance()->Late_Update();
}

void CJWScene::Render(HDC hDC)
{
	Rectangle(hDC, -100, -100, 900, 700);
	// À­¸é
	MoveToEx(hDC, 100, 50, nullptr);
	LineTo(hDC, 700, 50);
	LineTo(hDC, 750, 100);
	LineTo(hDC, 50, 100);
	LineTo(hDC, 100, 50);

	// ¾Õ¸é
	MoveToEx(hDC, 50, 100, nullptr);
	LineTo(hDC, 50, 550);
	LineTo(hDC, 750, 550);
	LineTo(hDC, 750, 100);

	// ¿À¸¥ÂÊ¸é
	MoveToEx(hDC, 750, 550, nullptr);
	LineTo(hDC, 700, 500);
	LineTo(hDC, 700, 50);

	// ¿ÞÂÊ¸é
	MoveToEx(hDC, 50, 550, nullptr);
	LineTo(hDC, 100, 500);
	LineTo(hDC, 100, 50);

	// ¹Ø¸é À§
	MoveToEx(hDC, 100, 500, nullptr);
	LineTo(hDC, 700, 500);
	if (g_bDevmode) {
		TCHAR szWhoScene[64];
		_stprintf_s(szWhoScene, _T("Àå¿ø"));
		SetTextColor(hDC, RGB(0, 0, 0));
		//SetBkMode(hDC, TRANSPARENT);
		TextOut(hDC, 300, 10, szWhoScene, _tcslen(szWhoScene));
	}
	CObjectManager::Get_Instance()->Render(hDC);
	CUiManager::Get_Instance()->Render(hDC);
}

void CJWScene::Release()
{
	for (auto& pool : m_FruitPoolMap)
	{
		Safe_Delete(pool.second);
	}
	m_FruitPoolMap.clear();

	CObjectManager::Get_Instance()->Release();
	CObjectManager::Get_Instance()->RenderList_Clear();
}

void CJWScene::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
		g_bDevmode = !g_bDevmode;
	}

	if (CKeyManager::Get_Instance()->Key_Down(VK_F9)) {
		CSceneManager::Get_Instance()->Set_Scene(SC_MENU);
	}

	if (CKeyManager::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (m_bCreated)
		{
			m_dwDroppedTime = GetTickCount64();
			m_bCreated = false;
		}
	}
}

void CJWScene::Create_MapObj()
{
	if (!m_bCreated)
	{
		auto dwCur = GetTickCount64();
		if (dwCur - m_dwDroppedTime >= m_dwDropDelay)
		{
			m_bCreated = true;
			CObjectManager::Get_Instance()->Add_Object(OBJ_PLAYER, m_FruitPoolMap[FRUIT_TYPE::ORANGE]->Get_Obj());
		}
	}
}

void CJWScene::Offset()
{
}
