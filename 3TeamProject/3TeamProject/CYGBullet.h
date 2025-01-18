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
	void Set_Dir(D3DXVECTOR3 _look) { m_tInfo.vDir = _look; } //�÷��̾ ���� �������� �Ѿ��� �̵�
private:
	int m_iReMoveTick;
};

