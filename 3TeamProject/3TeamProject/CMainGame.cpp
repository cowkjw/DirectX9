#include "pch.h"
#include "CMainGame.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CKeyManager.h"
#include "CUiManager.h"
#include "CScrollManager.h"
#include "CSceneManager.h"
#include "CObjectManager.h"

bool g_bDevmode = false;

CMainGame::CMainGame() 
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
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
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
}

void CMainGame::Release()
{
	CKeyManager::Destroy_Instance();
	CUiManager::Destroy_Instance();
	CScrollManager::Destroy_Instance();
	CSceneManager::Destroy_Instance();
	CObjectManager::Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
