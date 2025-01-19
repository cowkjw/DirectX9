#include "pch.h"
#include "CCYFood.h"

void CCYFood::Initialize()
{
	m_eOBJID = OBJ_MISC;
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vPos = { (float)(rand() % 740 + 30), (float)(rand() % 540 + 30), 0.f };
	m_fSpeed = (float)(rand() % 3 + 1) * (float)(rand() % 2 == 0 ? 1 : -1);
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_tInfo.fSizeX = m_tInfo.fSizeY = (float)(rand() % 18 + 8);
	CCYObject::Initialize_OriginPoint(rand() % 3 + 3, (int)(m_tInfo.fSizeX / 2));
	randomcolor = RGB(rand() % 255, rand() % 255, rand() % 255);

}

int CCYFood::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_fAngle += m_fSpeed;

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = matRotZ * matTrans;

	for (int i = 0; i < m_vOriginPointvec.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vPointvec[i], &m_vOriginPointvec[i], &m_tInfo.matWorld);
		m_pRenderPoint[i].x = m_vPointvec[i].x;
		m_pRenderPoint[i].y = m_vPointvec[i].y;
	}

	__super::Update_Rect();

    return OBJ_NOEVENT;
}

void CCYFood::Late_Update()
{
}

void CCYFood::Render(HDC hDC)
{
	if (g_bDevmode) {
		HitCircle(hDC, m_tHitRect, 0, 0);
	}
	HPEN hPen = CreatePen(PS_SOLID, 3,randomcolor);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);


	HBRUSH RandBrush = CreateSolidBrush(randomcolor);
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, RandBrush);

	Polygon(hDC, m_pRenderPoint, m_vOriginPointvec.size());

	SelectObject(hDC, OldBrush); DeleteObject(RandBrush);
	SelectObject(hDC, hOldPen); DeleteObject(hPen);


}

void CCYFood::Release()
{
}

void CCYFood::OnCollision(CObject* _obj)
{
	m_bDead = true;
}
