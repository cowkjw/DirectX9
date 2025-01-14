#include "pch.h"
#include "CMainGame.h"

CMainGame::CMainGame() :m_pPlayer(nullptr), m_pMonster(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	if (!m_pPlayer) {
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}

	if (!m_pMonster) {
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}

	dynamic_cast<CMonster*>(m_pMonster)->Set_Player(m_pPlayer);
}

void CMainGame::Update()
{
	m_pPlayer->Update();
	m_pMonster->Update();
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	m_pPlayer->Render(m_hDC);
	m_pMonster->Render(m_hDC);
}

void CMainGame::Release()
{
	Safe_Delete<CObject*>(m_pPlayer);
	Safe_Delete<CObject*>(m_pMonster);

	ReleaseDC(g_hWnd, m_hDC);
}
