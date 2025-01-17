#include "pch.h"
#include "CJWScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CUiManager.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"
#include <time.h>

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
	srand(unsigned int(time(nullptr)));
	m_dwDropDelay = 1000ULL;
	m_dwDroppedTime = GetTickCount64();
	m_bCreated = true;
	m_iLevel = 3;
	for (int i = 0; i < (int)FRUIT_TYPE::END; i++)
	{
		if (!m_FruitPoolMap[(FRUIT_TYPE)i])
		{
			m_FruitPoolMap[(FRUIT_TYPE)i] = new CObjPool<CFruit>(20);
		}
	}
	//CObjectManager::Get_Instance()->Add_Object(OBJ_PLAYER, m_FruitPoolMap[FRUIT_TYPE::ORANGE]->Get_Obj());

	CUiManager::Get_Instance()->Set_UiType(UI_JW);
}

int CJWScene::Update()
{
	Key_Input();
	auto& fruitList = CObjectManager::Get_Instance()->Get_ObjList_ByID(OBJ_PLAYER);
	CCollisionManager::JW_Collision_Circle(fruitList, fruitList);
	Create_MapObj();
	CObjectManager::Get_Instance()->Update();
	return 0;
}

void CJWScene::Late_Update()
{
	

	CObjectManager::Get_Instance()->Late_Update();
}

void CJWScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	Render_Box(hDC);
	if (g_bDevmode) {
		TCHAR szWhoScene[64];
		_stprintf_s(szWhoScene, _T("장원"));
		SetTextColor(hDC, RGB(0, 0, 0));
		//SetBkMode(hDC, TRANSPARENT);
		TextOut(hDC, 300, 10, szWhoScene, _tcslen(szWhoScene));
	}
	CObjectManager::Get_Instance()->Render(hDC);
	CUiManager::Get_Instance()->Render(hDC);
}

void CJWScene::Release()
{
	CObjectManager::Get_Instance()->Release();
	CObjectManager::Get_Instance()->RenderList_Clear();
	for (auto& pool : m_FruitPoolMap)
	{
		Safe_Delete(pool.second);
	}
	m_FruitPoolMap.clear();
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
			FRUIT_TYPE eType = (FRUIT_TYPE)(rand() % m_iLevel);
			CObject* pObj = m_FruitPoolMap[eType]->Get_Obj();
			static_cast<CFruit*>(pObj)->Set_Type(eType);
			static_cast<CFruit*>(pObj)->Reset();
			CObjectManager::Get_Instance()->Add_Object(OBJ_PLAYER, pObj);
		}
	}
}

void CJWScene::Offset()
{
}

void CJWScene::Render_Box(HDC hDC)
{
	// 뒷면 (연한 보라)
	POINT backPoints[] = {
		{100, 50}, {700, 50}, {700, 500}, {50, 500}
	};
	HBRUSH lightPurpleBrush = CreateSolidBrush(RGB(200, 180, 255));  // 연한 보라
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, lightPurpleBrush);
	Polygon(hDC, backPoints, 4);

	// 밑면 (연한 보라)
	POINT bottomPoints[] = {
		{100, 500}, {700, 500}, {750, 550}, {50, 550}
	};
	Polygon(hDC, bottomPoints, 4);

	// 왼쪽면 (진한 보라)
	POINT leftPoints[] = {
		{50, 100}, {100, 50}, {100, 500}, {50, 550}
	};
	HBRUSH darkPurpleBrush = CreateSolidBrush(RGB(150, 100, 255));  // 진한 보라
	SelectObject(hDC, darkPurpleBrush);
	Polygon(hDC, leftPoints, 4);

	// 오른쪽면 (진한 보라)
	POINT rightPoints[] = {
		{700, 50}, {750, 100}, {750, 550}, {700, 500}
	};
	Polygon(hDC, rightPoints, 4);
	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));  // 선 굵기를 3으로 설정
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	// 선 그리기
	MoveToEx(hDC, 100, 50, nullptr);
	LineTo(hDC, 700, 50);
	LineTo(hDC, 750, 100);
	LineTo(hDC, 50, 100);
	LineTo(hDC, 100, 50);

	MoveToEx(hDC, 50, 100, nullptr);
	LineTo(hDC, 50, 550);
	LineTo(hDC, 750, 550);
	LineTo(hDC, 750, 100);

	MoveToEx(hDC, 750, 550, nullptr);
	LineTo(hDC, 700, 500);
	LineTo(hDC, 700, 50);

	MoveToEx(hDC, 50, 550, nullptr);
	LineTo(hDC, 100, 500);
	LineTo(hDC, 100, 50);

	MoveToEx(hDC, 100, 500, nullptr);
	LineTo(hDC, 700, 500);

	// 리소스 정리
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(hPen);
	DeleteObject(lightPurpleBrush);
	DeleteObject(darkPurpleBrush);
}
