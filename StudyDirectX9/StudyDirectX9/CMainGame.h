#pragma once
#include "Define.h"

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
};

