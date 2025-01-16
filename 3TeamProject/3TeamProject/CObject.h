#pragma once
#include "Define.h"

class CObject
{
public:
	CObject();
	virtual ~CObject();
public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;
	virtual void OnCollision(CObject* _obj) PURE;
public:
	const RENDERID Get_GroupID() const { return m_eRender; }
	INFO		Get_Info() { return m_tInfo; }
	float		Get_Speed() { return m_fSpeed; }
public:
	void Set_Pos(float _x, float _y) { m_tInfo.vPos.x = _x, m_tInfo.vPos.y = _y; }
	void Set_Size(float _x, float _y) { m_tInfo.fSizeX= _x, m_tInfo.fSizeY = _y; }
	void Set_TargetObj(CObject* _obj) { m_targetObj = _obj; }
public:
	void		Update_Rect();
protected:
	OBJID		m_eOBJID;
	RENDERID	m_eRender;

	INFO m_tInfo;
	RECT m_tHitRect;
	float m_fSpeed;

	CObject* m_targetObj;
};

