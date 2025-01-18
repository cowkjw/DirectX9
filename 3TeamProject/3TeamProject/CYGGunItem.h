#pragma once
#include "CYGItem.h"
class CYGGunItem :public CYGItem
{
public:
	CYGGunItem();
	virtual ~CYGGunItem();
public:
	void Render(HDC hDC);
};

