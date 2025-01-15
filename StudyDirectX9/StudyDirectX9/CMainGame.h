#pragma once
#include "Define.h"
#include "CPlayer.h"
#include "CMonster.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
private:
	HDC m_hDC;

	CObject* m_pPlayer;
};

