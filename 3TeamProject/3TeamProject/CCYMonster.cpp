#include "pch.h"
#include "CCYMonster.h"
#include "CCYTail.h"
#include "CCollisionManager.h"
#include "CObjectManager.h"

void CCYMonster::Initialize()
{
	m_eOBJID = OBJ_MONSTER;
	m_eRender = RENDER_GAMEOBJECT;

	//rand() % 2 == 0 ? (m_tInfo.vPos.x = 0, m_tInfo.vPos.y = rand() % 600) : (m_tInfo.vPos.x = rand() % 800, m_tInfo.vPos.y = 0);
	//m_tInfo.vPos = { 400.f, 300.f, 0.f };

	switch (rand()%4)
	{
	case 0:
		m_tInfo.vPos = { 0.f, (float)(rand() % 600), 0.f };
		m_fAngle = 180;
		break;
	case 1:
		m_tInfo.vPos = { 800.f, (float)(rand() % 600), 0.f };
		m_fAngle = 0;
		break;
	case 2:
		m_tInfo.vPos = { (float)(rand() % 800), 0.f, 0.f };
		m_fAngle = 270;
		break;
	case 3:
		m_tInfo.vPos = { (float)(rand() % 800), 600.f, 0.f };
		m_fAngle = 90;
		break;
	default:
		break;
	}



	m_fSpeed = rand()%3 * 1.2 + 1;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	CCYObject::Initialize_OriginPoint(12, 16);
	m_WormColor = RGB(rand()%235 + 20, rand() % 235 + 20, rand() % 235 + 20);
	for (int i = 0; i < rand() % 150 + 30; ++i)
	{
		Increase_TailSegment();
	}
	//m_fAngle = rand() % 365;
}

int CCYMonster::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	if (m_ullRandomTicker + 500 < GetTickCount64())
	{
		m_fAngle += rand() % 5 * 3 + 5 * (rand() % 2 == 0 ? 1 : -1);
		m_ullRandomTicker = GetTickCount64();
	}

	m_tInfo.vPos.x -= cosf(D3DXToRadian(m_fAngle)) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(D3DXToRadian(m_fAngle)) * m_fSpeed;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	m_tInfo.matWorld = matRotZ * matTrans;
	for (int i = 0; i < m_vOriginPointvec.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vPointvec[i], &m_vOriginPointvec[i], &m_tInfo.matWorld);
		m_pRenderPoint[i].x = m_vPointvec[i].x;
		m_pRenderPoint[i].y = m_vPointvec[i].y;
	}
	for (auto& pTail : m_TailSeglist)
	{
		pTail->Update();
	}
	auto iter = m_TailSeglist.rbegin();
	if ((*iter)->Get_Info().vPos.x < 0
		|| (*iter)->Get_Info().vPos.y < 0
		|| (*iter)->Get_Info().vPos.x > 800
		|| (*iter)->Get_Info().vPos.y > 600)
	{
		m_bDead = true;
	}
	__super::Update_Rect();

    return 0;
}

void CCYMonster::Late_Update()
{
	CCollisionManager::Collision_Circle(OBJMGR->Get_ObjList_ByID(OBJ_PLAYER), m_TailSeglist);

	for (auto& pTail : m_TailSeglist)
	{
		pTail->Late_Update();
	}
}

void CCYMonster::Render(HDC hDC)
{
	if (g_bDevmode) {
		HitCircle(hDC, m_tHitRect, 0, 0);
	}

	for (auto iter = m_TailSeglist.rbegin(); iter != m_TailSeglist.rend(); ++iter)
	{
		(*iter)->Render(hDC);
	}

	HPEN hPen = CreatePen(PS_SOLID, 3, m_WormColor);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH PinkBrush = CreateSolidBrush(m_WormColor);
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, PinkBrush);

	Polygon(hDC, m_pRenderPoint, m_vOriginPointvec.size());

	SelectObject(hDC, OldBrush); DeleteObject(PinkBrush);
	SelectObject(hDC, hOldPen); DeleteObject(hPen);

}

void CCYMonster::Release()
{
	for_each(m_TailSeglist.begin(), m_TailSeglist.end(), Safe_Delete<CObject*>);

}

void CCYMonster::OnCollision(CObject* _obj)
{
}

void CCYMonster::Increase_TailSegment()
{
	CObject* pTail = new CCYTail;

	static_cast<CCYTail*>(pTail)->Set_TargetHead(this);

	if (m_TailSeglist.empty())
	{
		pTail->Set_TargetObj(this);
	}
	else
	{
		pTail->Set_TargetObj(m_TailSeglist.back());
	}

	pTail->Initialize();
	m_TailSeglist.push_back(pTail);
}