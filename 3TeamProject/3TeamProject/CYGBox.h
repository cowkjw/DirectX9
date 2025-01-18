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
private: 
	D3DXVECTOR3 m_vOutBox[4];
	D3DXVECTOR3 m_vOriginOutBox[4];
	D3DXVECTOR3 m_vInBox[4];
	D3DXVECTOR3 m_vOriginInBox[4];
};

