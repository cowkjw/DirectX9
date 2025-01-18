#pragma once

#include "CDWObject.h"

class CRoad : public CDWObject
{
	struct Obstacle
	{
		D3DXVECTOR3 vPos;   
		D3DXVECTOR3 vSize; 
		float fScale;     
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

private:
	D3DXVECTOR3     m_vPoint[4];
	D3DXVECTOR3     m_vOriginPoint[4];


	D3DXMATRIX        matScale_Sosil;  // ũ��
	D3DXMATRIX        matRotZ_Sosil; // ����
	D3DXMATRIX        matTrans_Sosil; // ��ġ

	D3DXMATRIX WorldMat_Sosil;

	D3DXVECTOR3 transformedCorners[4]; // ��İ����ع��� ����

	D3DXVECTOR3 rotatedSosil[4];


	D3DXVECTOR3 m_vCorner[4];
	D3DXVECTOR3 Sosil[4];



	float m_fTargetAngle;


	static bool m_bLeft_Rotation;
	static bool m_bRight_Rotation;

	bool m_bFirst_Check;

	CObject* m_pPlayer;

	vector<POINT*> m_vecPoints; // ���;ȿ� ����Ʈ��� 4��¥���迭��`

	vector<Obstacle> m_Obstacles;

	Obstacle obs = {}; 
	


};

