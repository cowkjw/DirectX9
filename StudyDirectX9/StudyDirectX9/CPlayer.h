#pragma once
#include "CObject.h"
class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer() { Release(); }
public:
	void Initialize() override;
	void Update() override;
	void Render(HDC hDC) override;
	void Release() override;
private:
	D3DXVECTOR3 leftTop;
	D3DXVECTOR3 rightTop;
	D3DXVECTOR3 leftBottom;
	D3DXVECTOR3 rightBottom;

	D3DXVECTOR3 m_tPosin;
	float m_fAngle;
};

