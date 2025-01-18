#pragma once
#include "CYGObject.h"
class CYGItem :public CYGObject
{
public:
	CYGItem();
	virtual ~CYGItem() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;
private:
	void OnCollision();
};

