#include "pch.h"
#include "CRoad.h"
#include "CKeyManager.h"
#include "CObjectManager.h"

bool CRoad::m_bLeft_Rotation = false;
bool CRoad::m_bRight_Rotation = false;

CRoad::CRoad()
{

}

void CRoad::Initialize()
{
	m_eOBJID = OBJ_DW_ROAD;
	m_eRender = RENDER_BACKGROUND;

	m_tInfo.vPos = { 400.f, -900.f, 0.f };
	m_fSpeed = 10.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fAngle = 0.f;
	m_fTargetAngle = 0.f; // �ʱ� ��ǥ ���� ����

	m_vCorner[0] = { -1500, -1500, 0 }; // ������
	m_vCorner[1] = { 1500, -1500, 0 };  // ��������
	m_vCorner[2] = { 1500, 1500, 0 };   // ������ �Ʒ�
	m_vCorner[3] = { -1500, 1500, 0 };  // ���� �Ʒ�

	Sosil[0] = { 350.f, 250.f, 0.f }; // ���� ��
	Sosil[1] = { 450.f, 250.f, 0.f }; // ������ ��
	Sosil[2] = { 450.f, 350.f, 0.f }; // ������ �Ʒ�
	Sosil[3] = { 350.f, 350.f, 0.f }; // ���� �Ʒ�

	m_vecPoints.push_back(new POINT[4]{}); // ���ʸ�
	m_vecPoints.push_back(new POINT[4]{}); // �����ʸ�
	m_vecPoints.push_back(new POINT[4]{}); // ����
	m_vecPoints.push_back(new POINT[4]{}); // �Ʒ���
	m_vecPoints.push_back(new POINT[4]{}); // �߾Ӹ�



	obs.vPos = { 400.f, 100.f, 0.f };   // �ʱ� ��ġ (ȭ�� ��)
	obs.vSize = { 50.f, 50.f, 0.f };    // �ʱ� ũ��
	obs.fScale = 1.0f;                  // �ʱ� ������

	m_Obstacles.push_back(obs);

	Wall_Update();

	m_pPlayer = CObjectManager::Get_Instance()->Get_ObjList_ByID(OBJ_PLAYER).front();

	m_bFirst_Check = false;
}

void CRoad::Wall_Update()
{
		m_vecPoints[0][0] = { (long)transformedCorners[0].x, (long)transformedCorners[0].y };
		m_vecPoints[0][1] = { (long)rotatedSosil[0].x, (long)rotatedSosil[0].y };
		m_vecPoints[0][2] = { (long)rotatedSosil[3].x, (long)rotatedSosil[3].y };
		m_vecPoints[0][3] = { (long)transformedCorners[3].x, (long)transformedCorners[3].y };


		m_vecPoints[1][0] = { (long)transformedCorners[1].x, (long)transformedCorners[1].y };
		m_vecPoints[1][1] = { (long)rotatedSosil[1].x, (long)rotatedSosil[1].y };
		m_vecPoints[1][2] = { (long)rotatedSosil[2].x, (long)rotatedSosil[2].y };
		m_vecPoints[1][3] = { (long)transformedCorners[2].x, (long)transformedCorners[2].y };
	
		m_vecPoints[2][0] = { (long)transformedCorners[0].x, (long)transformedCorners[0].y };
		m_vecPoints[2][1] = { (long)rotatedSosil[0].x, (long)rotatedSosil[0].y };
		m_vecPoints[2][2] = { (long)rotatedSosil[1].x, (long)rotatedSosil[1].y };
		m_vecPoints[2][3] = { (long)transformedCorners[1].x, (long)transformedCorners[1].y };

		m_vecPoints[3][0] = { (long)transformedCorners[3].x, (long)transformedCorners[3].y };
		m_vecPoints[3][1] = { (long)rotatedSosil[3].x, (long)rotatedSosil[3].y };
		m_vecPoints[3][2] = { (long)rotatedSosil[2].x, (long)rotatedSosil[2].y };
		m_vecPoints[3][3] = { (long)transformedCorners[2].x, (long)transformedCorners[2].y };

		m_vecPoints[4][0] = { (long)rotatedSosil[0].x, (long)rotatedSosil[0].y };
		m_vecPoints[4][1] = { (long)rotatedSosil[1].x, (long)rotatedSosil[1].y };
		m_vecPoints[4][2] = { (long)rotatedSosil[2].x, (long)rotatedSosil[2].y };
		m_vecPoints[4][3] = { (long)rotatedSosil[3].x, (long)rotatedSosil[3].y };


	
}


int CRoad::Update()
{
	Key_Input();
	//if (m_bRight_Rotation)
	//{
	//	//static float m_Move = 20.f;
	//	//m_pPlayer->Set_Pos(m_pPlayer->Get_Info().vPos.x - m_Move, 550.f);

	//	//if (m_pPlayer->Get_Info().vPos.x < 210)
	//	//	m_bRight_Rotation = false;
	//}


	if (abs(m_fTargetAngle - m_fAngle) > D3DXToRadian(1.f)) 
	{
		if (m_fTargetAngle > m_fAngle)
			m_fAngle += D3DXToRadian(5.f);
		else if (m_fTargetAngle < m_fAngle)
			m_fAngle -= D3DXToRadian(5.f);
	}

	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	WorldMat = matRotZ * matTrans;

	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&transformedCorners[i], &m_vCorner[i], &WorldMat);
	}

	


	D3DXVECTOR3 sosilCenter =
	{
		(Sosil[0].x + Sosil[2].x) / 2.f,
		(Sosil[0].y + Sosil[2].y) / 2.f,
		0.f
	};

	float rotationAngle = m_fAngle;

	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR3 relativePoint = { Sosil[i].x - sosilCenter.x, Sosil[i].y - sosilCenter.y, 0.f };

		float rotatedX = relativePoint.x * cos(rotationAngle) - relativePoint.y * sin(rotationAngle);
		float rotatedY = relativePoint.x * sin(rotationAngle) + relativePoint.y * cos(rotationAngle);

		rotatedSosil[i].x = rotatedX + sosilCenter.x;
		rotatedSosil[i].y = rotatedY + sosilCenter.y;
		rotatedSosil[i].z = 0.f;
	}

	Wall_Update();

	for (auto& obs : m_Obstacles)
	{
		obs.vPos.y += 5.f;  // Y�� ��ֹ� �̵�
		obs.fScale -= 0.01f; // �Ÿ��� ����� ������ �����ϴ°�
		if (obs.fScale <= 0.1f)
		{
			obs.fScale = 0.1f; // �ּ� ũ�⿡��
		}
	}

	__super::Update_Rect();
	return 0;

}
void CRoad::Key_Input()
{

	if (GetAsyncKeyState('A'))
	{
		// ��θ� ��������
		D3DXVECTOR3 fixedLeftDir = { +20.f, 0.f, 0.f };
		m_tInfo.vPos += fixedLeftDir; 

		// ���߿� ù�浹�� 270��ǥ�� �ٲٵ�
		// ó�� ��� ��ġ��ǥ�� �ٲٵ� �� ����
		/*if (m_pPlayer->Get_Info().vPos.x < 320)
		{
			m_bLeft_Rotation = !m_bLeft_Rotation;
			m_fTargetAngle += D3DXToRadian(90.f); 
			m_tInfo.vPos = { 0.f, 0.f, 0.f };
			m_bRight_Rotation = true;
		}*/
	}


	else if (GetAsyncKeyState('D'))
	{
	    // ��θ� ����������
		D3DXVECTOR3 fixedRightDir = { -20.f, 0.f, 0.f };
		m_tInfo.vPos += fixedRightDir; 

		/*if (m_pPlayer->Get_Info().vPos.x > 640)
		{
			m_bRight_Rotation = !m_bRight_Rotation;
			m_fTargetAngle += D3DXToRadian(-90.f);
			m_tInfo.vPos = { 0.f, 0.f, 0.f };
			m_bRight_Rotation = true;
		}*/
	
	}

	// ȭ�� ���� ����
	if (GetAsyncKeyState('W'))
	{
		
		D3DXVECTOR3 fixedDownDir = { 0.f, 40.f, 0.f };
		m_tInfo.vPos += fixedDownDir;
	}

	//  ȭ�� ���� �Ʒ���
	else if (GetAsyncKeyState('S'))
	{
		D3DXVECTOR3 fixedUpDir = { 0.f, -40.f, 0.f };
		m_tInfo.vPos += fixedUpDir;
	}

	// ���� �������� 90�� ȸ��
	if (CKeyManager::Get_Instance()->Key_Down(VK_LEFT))
	{
		m_bRight_Rotation = !m_bRight_Rotation;
		m_fTargetAngle -= D3DXToRadian(90.f);	
	}
	if (m_tInfo.vPos.x > 1900)
	{
		m_bRight_Rotation = !m_bRight_Rotation;
		m_fTargetAngle -= D3DXToRadian(90.f);
		m_tInfo.vPos.x = -1140;

		static float m_Move = 20.f;
		//m_tInfo.vPos.x += m_Move;

		//if (m_tInfo.vPos.x > 610)
			
		
	}
	// ������ �������� 90�� ȸ��
	if (CKeyManager::Get_Instance()->Key_Down(VK_RIGHT))
	{
		m_bLeft_Rotation = !m_bLeft_Rotation;
		m_fTargetAngle += D3DXToRadian(-90.f);
	}
	if (m_tInfo.vPos.x < -1140)
	{
		m_bRight_Rotation = !m_bRight_Rotation;
		m_fTargetAngle -= D3DXToRadian(-90.f);
		m_tInfo.vPos.x = 1900;

	}

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		D3DXVECTOR3 fixedForwardDir = { 0.f, 40.f, 0.f };
		m_tInfo.vPos += fixedForwardDir;
	}
}


//
//HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 220, 220));
//HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
//SelectObject(hDC, hOldPen); DeleteObject(hPen);


void CRoad::Late_Update()
{
}
void CRoad::Render(HDC hDC)
{
	// ī�޶� ȭ��


	

	MoveToEx(hDC, transformedCorners[0].x, transformedCorners[0].y, nullptr);
	LineTo(hDC, transformedCorners[1].x, transformedCorners[1].y);
	LineTo(hDC, transformedCorners[2].x, transformedCorners[2].y);
	LineTo(hDC, transformedCorners[3].x, transformedCorners[3].y);
	LineTo(hDC, transformedCorners[0].x, transformedCorners[0].y);



	// �ҽ��� �׸� 
	MoveToEx(hDC, rotatedSosil[0].x, rotatedSosil[0].y, nullptr);
	LineTo(hDC, rotatedSosil[1].x, rotatedSosil[1].y);
	LineTo(hDC, rotatedSosil[2].x, rotatedSosil[2].y);
	LineTo(hDC, rotatedSosil[3].x, rotatedSosil[3].y);
	LineTo(hDC, rotatedSosil[0].x, rotatedSosil[0].y);

	
	


	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(128, 128, 128));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);





	// ó�� ���� ���� ��
	HBRUSH GrayBrush = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, GrayBrush);

	Polygon(hDC, m_vecPoints[0], 4);

	SelectObject(hDC, OldBrush);
	DeleteObject(GrayBrush);

	// ó�� ���� ������ ��
	HBRUSH GrayBrush1 = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH OldBrush1 = (HBRUSH)SelectObject(hDC, GrayBrush1);

	Polygon(hDC, m_vecPoints[1], 4);

	SelectObject(hDC, OldBrush1);
	DeleteObject(GrayBrush1);

	// ó�� ���� ������ ��
	HBRUSH GrayBrush2 = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH OldBrush2 = (HBRUSH)SelectObject(hDC, GrayBrush2);

	Polygon(hDC, m_vecPoints[2], 4);

	SelectObject(hDC, OldBrush2);
	DeleteObject(GrayBrush2);

	HBRUSH GrayBrush3 = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH OldBrush3 = (HBRUSH)SelectObject(hDC, GrayBrush3);

	Polygon(hDC, m_vecPoints[3], 4);

	SelectObject(hDC, OldBrush3);
	DeleteObject(GrayBrush3);

	HBRUSH GrayBrush4 = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH OldBrush4 = (HBRUSH)SelectObject(hDC, GrayBrush4);

	Polygon(hDC, m_vecPoints[4], 4);

	SelectObject(hDC, GrayBrush4);
	DeleteObject(OldBrush4);


	HBRUSH GrayBrush5 = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH OldBrush5 = (HBRUSH)SelectObject(hDC, GrayBrush5);


	SelectObject(hDC, hOldPen); DeleteObject(hPen);
	SelectObject(hDC, GrayBrush5);
	DeleteObject(OldBrush5);


	if (g_bDevmode)
	{
		HitCircle(hDC, m_tHitRect, 0, 0);
	}


	 hPen = CreatePen(PS_SOLID, 3, RGB(128, 128, 128));
	 hOldPen = (HPEN)SelectObject(hDC, hPen);
	
	SelectObject(hDC, hOldPen); DeleteObject(hPen);

	for (int i = 0; i < 4; ++i)
	{
		MoveToEx(hDC, transformedCorners[i].x, transformedCorners[i].y, nullptr);
		LineTo(hDC, rotatedSosil[i].x, rotatedSosil[i].y);
	}

	for (const auto& ons : m_Obstacles)
	{
		D3DXMATRIX matScale, matTrans, matWorld;
		
		D3DXMatrixScaling(&matScale, obs.fScale, obs.fScale, 1.0f);
		D3DXMatrixTranslation(&matTrans, obs.vPos.x, obs.vPos.y, 0.0f);
		matWorld = matScale * matTrans;

		RECT rect = {
		(LONG)(obs.vPos.x - obs.vSize.x * obs.fScale / 2),
		(LONG)(obs.vPos.y - obs.vSize.y * obs.fScale / 2),
		(LONG)(obs.vPos.x + obs.vSize.x * obs.fScale / 2),
		(LONG)(obs.vPos.y + obs.vSize.y * obs.fScale / 2)
		};

		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, brush);
		Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(brush);


	}




	TCHAR m_szBuf[100] = {};
	swprintf_s(m_szBuf, L"��� x : %.f, ��� y : %.f", m_tInfo.vPos.x, m_tInfo.vPos.y);
	TextOut(hDC, 300, 30, m_szBuf, lstrlen(m_szBuf));
}


void CRoad::Release()
{
	for (auto& pointArray : m_vecPoints)
	{
		delete[] pointArray;
	}
	m_vecPoints.clear(); 
}

void CRoad::OnCollision(CObject* _obj)
{
}



