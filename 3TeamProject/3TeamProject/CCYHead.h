#pragma once
#include "CCYObject.h"
class CCYHead : public CCYObject
{
public:
	CCYHead(): m_fAngle(0.f) {}
	virtual ~CCYHead() {}
public:
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
	void OnCollision(CObject* _obj) PURE;

	int	 Get_WormLength() { if (m_TailSeglist.empty()) return 0; else return m_TailSeglist.size(); }

protected:
	D3DXMATRIX	matScale;
	D3DXMATRIX	matRotZ;
	D3DXMATRIX	matTrans;
	float       m_fAngle;
	D3DXVECTOR3 m_vEyePoint[4];
	list<CObject*> m_TailSeglist;
};

