#pragma once
#include "CYGObject.h"
class CYGBullet :public CYGObject
{
public:
	CYGBullet();
	virtual ~CYGBullet();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;
public:
	void Set_Dir(D3DXVECTOR3 _look) { m_tInfo.vDir = _look; } //플레이어가 보는 방향으로 총알이 이동
private:
	void OnCollision();
private:
	int m_iReMoveTick;
	bool m_bDead;
};

