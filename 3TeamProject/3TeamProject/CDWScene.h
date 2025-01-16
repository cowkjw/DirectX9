#pragma once
#include "CScene.h"
class CDWScene :public CScene
{
public:
	CDWScene();
	virtual ~CDWScene() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Key_Input() override;
	void Create_MapObj() override;
	void Offset() override;
};

