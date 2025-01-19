#pragma once
#include "CYGItem.h"
class CYGBulletItem :public CYGItem
{
public:
	CYGBulletItem();
	virtual ~CYGBulletItem();
public:
	int Update();
	void Render(HDC hDC);
};

