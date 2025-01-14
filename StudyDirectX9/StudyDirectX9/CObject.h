#pragma once
#include "Define.h"
class CObject
{
public:
	CObject();
	virtual ~CObject();
public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;
public:
	INFO		Get_Info() { return m_tInfo; }
protected:
	INFO m_tInfo;
	float m_fSpeed;
};

