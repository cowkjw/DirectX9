#pragma once
#include "CYGObject.h"
class CYGPlayer :public CYGObject
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
	void Key_Input();
private:
	D3DXVECTOR3 leftHandPos;
	D3DXVECTOR3 rightHandPos;

	D3DXVECTOR3 m_vOriginPos;
	D3DXVECTOR3 m_vOriginLeftHand;
	D3DXVECTOR3 m_vOriginRightHand;
};

