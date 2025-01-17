#include "pch.h"
#include "CMainGame.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CKeyManager.h"
#include "CUiManager.h"
#include "CScrollManager.h"
#include "CSceneManager.h"
#include "CObjectManager.h"
#include "CBitManager.h"

bool g_bDevmode = false;

CMainGame::CMainGame() 
{
	// CY CCYCYCYCYCYCY
	//¹Ý°©°í
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	CBitManager::Get_Instance()->Insert_Bmp(L"../Assets/Back/Back.bmp", L"Back");

	m_hDC = GetDC(g_hWnd);
	CSceneManager::Get_Instance()->Set_Scene(SC_MENU);
}

void CMainGame::Update()
{
	CSceneManager::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneManager::Get_Instance()->Late_Update();
	CKeyManager::Get_Instance()->Update();
}

void CMainGame::Render()
{
	HDC		hMemDC = CBitManager::Get_Instance()->Find_Image(L"Back");
	CSceneManager::Get_Instance()->Render(hMemDC);
	GdiTransparentBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 800, 600, SRCCOPY);
}

void CMainGame::Release()
{
	CKeyManager::Destroy_Instance();
	CUiManager::Destroy_Instance();
	CScrollManager::Destroy_Instance();
	CSceneManager::Destroy_Instance();
	CObjectManager::Destroy_Instance();
	CBitManager::Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
