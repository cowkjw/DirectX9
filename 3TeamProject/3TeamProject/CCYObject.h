#pragma once
#include "CObject.h"
class CCYObject : public CObject
{
public:
	CCYObject(): m_pRenderPoint(nullptr), m_fRadius(0.f) {}
	virtual ~CCYObject();
public:
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
	void OnCollision(CObject* _obj) PURE;

	void Initialize_OriginPoint(const int& _iCount, const int& _Radius, const float& _fStartAngle = 0.f);


protected:
	vector<D3DXVECTOR3> m_vOriginPointvec;
	vector<D3DXVECTOR3> m_vPointvec;

	float				m_fRadius;
	
	POINT*				m_pRenderPoint;
};

