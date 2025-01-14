#pragma once
#include "CObject.h"
class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer() { Release(); }
public:
	void Initialize() override;
	void Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

