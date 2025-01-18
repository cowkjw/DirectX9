#pragma once
#include "CYGItem.h"
class CYGBulletItem :public CYGItem
{
public:
	CYGBulletItem();
	virtual ~CYGBulletItem();
public:
	void Render(HDC hDC);
};

