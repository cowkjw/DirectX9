#include "pch.h"
#include "CCYTail.h"
#include "Define.h"
#include "CCollisionManager.h"

void CCYTail::Initialize()
{
	m_eOBJID = OBJ_END;
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_fSpeed = 2.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	CCYObject::Initialize_OriginPoint(12, 10);
}

int CCYTail::Update()
{


	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matTrans;
	for (int i = 0; i < m_vOriginPointvec.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vPointvec[i], &m_vOriginPointvec[i], &m_tInfo.matWorld);
		m_pRenderPoint[i].x = m_vPointvec[i].x;
		m_pRenderPoint[i].y = m_vPointvec[i].y;
	}



	m_tInfo.vDir = m_targetObj->Get_Info().vPos - m_tInfo.vPos;
	if (D3DXVec3Length(&m_tInfo.vDir) > 10)
	{
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	else
		return OBJ_NOEVENT;

	return OBJ_NOEVENT;
}

void CCYTail::Late_Update()
{
	
}

void CCYTail::Render(HDC hDC)
{
	if (g_bDevmode) {
		HitCircle(hDC, m_tHitRect, 0, 0);
	}
	HBRUSH PinkBrush = CreateSolidBrush(RGB(255, 220, 220));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, PinkBrush);

	Polygon(hDC, m_pRenderPoint, m_vOriginPointvec.size());
	SelectObject(hDC, OldBrush); DeleteObject(PinkBrush);


}

void CCYTail::Release()
{
}

void CCYTail::OnCollision(CObject* _obj)
{
}
