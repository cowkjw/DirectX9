#pragma once

#include "CDWObject.h"
#include <d3dx9math.h>  
class CRoad : public CDWObject
{
public:

	struct SObstacle
	{
		D3DXVECTOR3 vPos;   // 장애물의 월드 위치 (z축 포함)
		float       fWidth; // 장애물의 가로크기
		float       fHeight;// 장애물의 세로크기
		D3DXVECTOR3 worldCorner[4];
		float       fAngle; 
		float       fScale; // 스케일(배율)
	};

public:
	CRoad();
	virtual ~CRoad() { Release(); }
	void Initialize() override;
	int Update() override;
	void Key_Input();
	void Player_With_Obs_Call();
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;
    void Wall_Update();
	//////////////////////////////////////
	void Update_Obstacles();
	void Spawn_Obstacle();
	void Render_Obstacles(HDC hDC);
    /////////////////////////////////////


	auto& Get_obs()
	{
		return  m_Obstacles;
	}
	

private:
	D3DXVECTOR3 Sosil[4];
	D3DXVECTOR3 rotatedSosil[4];
	D3DXVECTOR3 m_vCorner[4];
	D3DXVECTOR3 transformedCorners[4]; // 행렬곱당해버릴 벡터
	D3DXMATRIX        matScale_Sosil;  // 크기
	D3DXMATRIX        matRotZ_Sosil; // 자전
	D3DXMATRIX        matTrans_Sosil; // 위치
	D3DXMATRIX WorldMat_Sosil; // 소실점 월드 행렬
	static bool m_bLeft_Rotation;
	static bool m_bRight_Rotation;
	static bool m_bTop_Rotation;
	static bool m_bBottom_Rotation;
	bool m_bFirst_Check;
	bool  m_bJumping;
	vector<POINT*> m_vecPoints; // 벡터안에 포인트라는 4개짜리배열을`	
	vector<SObstacle> m_Obstacles; // 장애물 구조체 보관
	CObject* m_pPlayer;
	DWORD m_dwPrevSpawnTime; // 스폰 조절할 타이머
	HBITMAP hBmp;
	HBRUSH  hPatternBrush;
private:    
	float m_fJumpSpeed;       
	float m_fGravity;         
	float m_fJumpOffsetY;   
	float m_fTargetAngle;
	float m_fTargetX;

	
};

