#pragma once
#include "CYGBox.h"
class CYGBulletBox :public CYGBox
{
public:
	CYGBulletBox();
	virtual ~CYGBulletBox() { Release(); }
public:
	int Update() override;
};

