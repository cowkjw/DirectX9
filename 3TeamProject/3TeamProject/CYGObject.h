#pragma once
#include "CObject.h"
class CYGObject :public CObject
{
public:
	CYGObject();
	virtual ~CYGObject() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;
protected:
	float m_fAngle;

	int m_iHp;
	int m_iMaxHp;
};

