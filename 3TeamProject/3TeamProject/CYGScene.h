#pragma once
#include "CScene.h"
class CYGScene :public CScene
{
public:
	CYGScene();
	virtual ~CYGScene() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Key_Input() override;
	void Create_MapObj() override;
	void Offset() override;
};

