#pragma once
#include "CYGObject.h"
class CYGBox :public CYGObject
{
public:
	CYGBox();
	virtual ~CYGBox();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;
public:
	RECT Get_HitBox() { return m_tHitRect; }
protected:
	void OnCollision();
protected: 
	D3DXVECTOR3 m_vOutBox[4];
	D3DXVECTOR3 m_vOriginOutBox[4];
	D3DXVECTOR3 m_vInBox[4];
	D3DXVECTOR3 m_vOriginInBox[4];
	int m_HitTick;
	float m_iScaleSize;

	float m_fOriginSizeX;
	float m_fOriginSizeY;
};

