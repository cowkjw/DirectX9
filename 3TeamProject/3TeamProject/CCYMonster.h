#pragma once
#include "CCYObject.h"
class CCYMonster :  public CCYObject
{
	// CCYObject을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;
};

