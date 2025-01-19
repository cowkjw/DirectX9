#pragma once
#include "CCYObject.h"
class CCYFood : public CCYObject
{
public:
	CCYFood() {}
	virtual ~CCYFood() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;

private:
	COLORREF	randomcolor;
};

