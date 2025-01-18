#pragma once
#include "CYGObject.h"
class CYGPunchMonster :public CYGObject
{
public:
	CYGPunchMonster();
	virtual ~CYGPunchMonster() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;
};

