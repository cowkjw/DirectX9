#pragma once
#include "CYGItem.h"
class CYGGunItem :public CYGItem
{
public:
	CYGGunItem();
	virtual ~CYGGunItem();
public:
	int Update() override;
	void Render(HDC hDC);
};

