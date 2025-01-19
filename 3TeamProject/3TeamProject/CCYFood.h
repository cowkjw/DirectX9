#pragma once
#include "CCYObject.h"
class CCYFood : public CCYObject
{
public:
	CCYFood() : m_ullLivingTime(0){}
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
	ULONGLONG	m_ullLivingTime;
};

