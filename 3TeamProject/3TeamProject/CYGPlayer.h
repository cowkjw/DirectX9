#pragma once
#include "CObject.h"
class CYGPlayer :public CObject
{
public:
	CYGPlayer();
	virtual ~CYGPlayer() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;

private:
	D3DXVECTOR3     m_vPoint[4];
	D3DXVECTOR3     m_vOriginPoint[4];
};

