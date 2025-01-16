#pragma once
#include "CObject.h"
class CDWPlayer :public CObject
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
	D3DXVECTOR3     m_vPoint[4];
	D3DXVECTOR3     m_vOriginPoint[4];


	D3DXMATRIX        matScale;  // 크기
	D3DXMATRIX        matRotZ, matRevZ; // 자전
	D3DXMATRIX        matTrans; // 위치


	D3DXMATRIX WorldMat;



	D3DXVECTOR3 transformedCorners[4]; // 행렬곱당해버릴 벡터
	D3DXVECTOR3 m_vCorner[4];

	float m_fNemoAngel;
};

void RenderBackground(HDC hDC, float playerSpeed);
