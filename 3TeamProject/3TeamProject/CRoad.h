#pragma once

#include "CDWObject.h"
#include <d3dx9math.h>  
class CRoad : public CDWObject
{
	struct SObstacle
	{
		D3DXVECTOR3 vPos;   // 장애물의 월드 위치 (z축 포함)
		float       fWidth; // 장애물의 가로크기
		float       fHeight;// 장애물의 세로크기
		float       fAngle; // Z축 기준 회전각 (2D게임이면 yaw 개념)
		float       fScale; // 스케일(배율)
	};



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
    void Wall_Update();

	void Update_Obstacles();

	void Render_Obstacles(HDC hDC);

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
	static bool m_bTop_Rotation;
	static bool m_bBottom_Rotation;

	bool m_bFirst_Check;

	CObject* m_pPlayer;

	vector<POINT*> m_vecPoints; // 벡터안에 포인트라는 4개짜리배열을`

	
	vector<SObstacle> m_Obstacles;


};

