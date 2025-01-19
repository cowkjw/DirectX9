#pragma once
#include "CYGObject.h"
class CYGMonster :public CYGObject
{
public:
	CYGMonster();
	virtual ~CYGMonster() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;
};

