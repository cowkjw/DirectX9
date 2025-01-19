#pragma once
#include "CCYHead.h"
class CCYMonster :  public CCYHead
{
public:
	CCYMonster() :m_ullRandomTicker(0){}
	virtual ~CCYMonster() { Release(); }

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;

	void Increase_TailSegment();

private:

	ULONGLONG	m_ullRandomTicker;

};

