#pragma once

#include "CDWObject.h"

class CRoad : public CDWObject
{
public:
	CRoad();
	virtual ~CRoad() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Key_Input();
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;

	bool CheckCollision(D3DXVECTOR3 playerPos, D3DXVECTOR3 lineStart, D3DXVECTOR3 lineEnd, float threshold);

private:
	D3DXVECTOR3     m_vPoint[4];
	D3DXVECTOR3     m_vOriginPoint[4];


	D3DXMATRIX        matScale_Sosil;  // 크기
	D3DXMATRIX        matRotZ_Sosil; // 자전
	D3DXMATRIX        matTrans_Sosil; // 위치

	D3DXMATRIX WorldMat_Sosil;

	D3DXVECTOR3 transformedCorners[4]; // 행렬곱당해버릴 벡터

	D3DXVECTOR3 rotatedSosil[4];


	D3DXVECTOR3 m_vCorner[4];
	D3DXVECTOR3 Sosil[4];



	float m_fTargetAngle;


	static bool m_bLeft_Rotation;
	static bool m_bRight_Rotation;

	bool m_bFirst_Check;

	CObject* m_pPlayer;
};

