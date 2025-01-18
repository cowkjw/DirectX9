#pragma once
#include "CDWObject.h"


class CDWPlayer :public CDWObject
{
public:
	CDWPlayer();
	virtual ~CDWPlayer() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Key_Input();
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;

private:
	
	D3DXVECTOR3 transformedCorners[4]; // ��İ����ع��� ����
	D3DXVECTOR3 m_vCorner[4];

};


