#pragma once
#include "CCYObject.h"
class CCYMonster :  public CCYObject
{
public:
	CCYMonster() :m_ullRandomTicker(0), m_fAngle(0){}
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
	D3DXMATRIX	matScale;
	D3DXMATRIX	matRotZ;
	D3DXMATRIX	matTrans;
	float       m_fAngle;
	D3DXVECTOR3 m_vEyePoint[4];

	ULONGLONG	m_ullRandomTicker;

	list<CObject*> m_TailSeglist;
};

