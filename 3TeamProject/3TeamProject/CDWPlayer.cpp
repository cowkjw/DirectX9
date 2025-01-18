#include "pch.h"
#include "CDWPlayer.h"
#include "CKeyManager.h"
#include "pch.h"
#include "CCYObject.h"

CDWPlayer::CDWPlayer()
{
}


void CDWPlayer::Initialize()
{
	m_eOBJID = OBJ_PLAYER;
	m_eRender = RENDER_GAMEOBJECT;




	m_tInfo.vPos = { 400.f, 500.f, 0.f };
	m_fSpeed = 2.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	CDWPlayer::Initialize_OriginPoint(30, 30);

}

int CDWPlayer::Update()
{
	//Key_Input();


	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);


	m_tInfo.matWorld =  matTrans;
	for (int i = 0; i < m_vOriginPointvec.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vPointvec[i], &m_vOriginPointvec[i], &m_tInfo.matWorld);
		m_pRenderPoint[i].x = m_vPointvec[i].x;
		m_pRenderPoint[i].y = m_vPointvec[i].y;
	}

	//__super::Update_Rect();
	return 0;
}

void CDWPlayer::Late_Update()
{
}

void CDWPlayer::Render(HDC hDC)
{
	if (g_bDevmode) 
	{
		HitCircle(hDC, m_tHitRect, 0, 0);
	}
	HBRUSH PinkBrush = CreateSolidBrush(RGB(255, 220, 220));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, PinkBrush);

	Polygon(hDC, m_pRenderPoint, m_vOriginPointvec.size());
	SelectObject(hDC, OldBrush); DeleteObject(PinkBrush);


	TCHAR m_szBuf[100] = {};
	swprintf_s(m_szBuf, L"플레이어 x : %.f, 플레이어 y : %.f", m_tInfo.vPos.x, m_tInfo.vPos.y);
	TextOut(hDC, 300, 5, m_szBuf, lstrlen(m_szBuf));

	


}

void CDWPlayer::Release()
{
}

void CDWPlayer::OnCollision(CObject* _obj)
{
}

void CDWPlayer::Key_Input()
{
	
	//if (GetAsyncKeyState('A'))
	//{
	//	m_tInfo.vDir = { -m_fSpeed, 0.f, 0.f };

	//	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);
	//	m_tInfo.vPos += m_tInfo.vDir;
	//}
	//if (GetAsyncKeyState('D'))
	//{
	//	m_tInfo.vDir = { m_fSpeed, 0.f, 0.f };

	//	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);
	//	m_tInfo.vPos += m_tInfo.vDir;
	//}
}

