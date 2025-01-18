#include "pch.h"
#include "CCYTail.h"
#include "Define.h"
#include "CCollisionManager.h"
#include "CCYPlayer.h"
#include "CObjectManager.h"

void CCYTail::Initialize()
{
	m_eOBJID = OBJ_CYTAIL;
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vPos = m_targetObj->Get_Info().vPos;
	m_fSpeed = 2.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_tInfo.fSizeX = m_tInfo.fSizeY = 24;
	CCYObject::Initialize_OriginPoint(12, 12);
	m_WormColor = static_cast<CCYObject*>(m_targetHead)->Get_WormColor();
}

int CCYTail::Update()
{
	m_fSpeed = m_targetHead->Get_Speed();

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	if (dynamic_cast<CCYPlayer*>(m_targetHead) == nullptr)
	{
		m_fWormSize = 1.f;
	}
	else
	{
		m_fWormSize = static_cast<CCYPlayer*>(m_targetHead)->Get_WormSize();

	}

	D3DXMatrixScaling(&matScale, m_fWormSize, m_fWormSize, 1.f);

	m_tInfo.matWorld = matScale * matTrans;
	for (int i = 0; i < m_vOriginPointvec.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vPointvec[i], &m_vOriginPointvec[i], &m_tInfo.matWorld);
		m_pRenderPoint[i].x = m_vPointvec[i].x;
		m_pRenderPoint[i].y = m_vPointvec[i].y;
	}


	m_tInfo.vDir = m_targetObj->Get_Info().vPos - m_tInfo.vPos;
	if (D3DXVec3Length(&m_tInfo.vDir) > 5)
	{
		//m_tInfo.vPos = m_targetObj->Get_Info().vPos;
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}
	else
	{
		__super::Update_Rect();
		return OBJ_NOEVENT;
	}

	__super::Update_Rect();
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

	HBRUSH PinkBrush = CreateSolidBrush(m_WormColor);
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, PinkBrush);
	HPEN hPen = CreatePen(PS_SOLID, 3, m_WormColor);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	Polygon(hDC, m_pRenderPoint, m_vOriginPointvec.size());
	SelectObject(hDC, OldBrush); DeleteObject(PinkBrush);
	SelectObject(hDC, hOldPen); DeleteObject(hPen);

}

void CCYTail::Release()
{
}

void CCYTail::OnCollision(CObject* _obj)
{
	if (_obj == m_targetHead)
	{
		return;
	}
	else
	{
		static_cast<CCYObject*>(m_targetHead)->Set_Dead();
		return;
	}
	if (_obj == GET_PLAYER)
	{
		if (m_targetHead != GET_PLAYER)
		{
			static_cast<CCYObject*>(m_targetHead)->Set_Dead();
		}
	}
}
