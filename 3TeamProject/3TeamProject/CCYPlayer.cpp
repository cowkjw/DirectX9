#include "pch.h"
#include "CCYPlayer.h"
#include "CCYObject.h"
#include "CCYTail.h"

CCYPlayer::CCYPlayer() :m_fAngle(0.f)
{
}

CCYPlayer::~CCYPlayer()
{
    Release();
}

void CCYPlayer::Initialize()
{
	m_eOBJID = OBJ_PLAYER;
	m_eRender = RENDER_GAMEOBJECT;




	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_fSpeed = 2.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	CCYObject::Initialize_OriginPoint(12, 10);

}

int CCYPlayer::Update()
{
	Key_Input();

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = matRotZ * matTrans;
	for (int i = 0; i < m_vOriginPointvec.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vPointvec[i], &m_vOriginPointvec[i], &m_tInfo.matWorld);
		m_pRenderPoint[i].x = m_vPointvec[i].x;
		m_pRenderPoint[i].y = m_vPointvec[i].y;
	}
	for (auto& pTail : m_TailSegvec)
	{
		pTail->Update();
	}
	__super::Update_Rect();
    return 0;
}

void CCYPlayer::Late_Update()
{
	for (auto& pTail : m_TailSegvec)
	{
		pTail->Late_Update();
	}
}

void CCYPlayer::Render(HDC hDC)
{
	if (g_bDevmode) {
		HitCircle(hDC, m_tHitRect, 0, 0);
	}
	for (auto iter = m_TailSegvec.rbegin(); iter != m_TailSegvec.rend(); ++iter)
	{
		(*iter)->Render(hDC);
	}

	HBRUSH PinkBrush = CreateSolidBrush(RGB(255, 220, 220));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, PinkBrush);

	Polygon(hDC, m_pRenderPoint, m_vOriginPointvec.size());
	SelectObject(hDC, OldBrush); DeleteObject(PinkBrush);


}

void CCYPlayer::Release()
{
	for_each(m_TailSegvec.begin(), m_TailSegvec.end(), Safe_Delete<CObject*>);
}

void CCYPlayer::OnCollision(CObject* _obj)
{
}

void CCYPlayer::Key_Input()
{
	if (GetAsyncKeyState('A'))
	{
		m_fAngle -= 5;
	}
	if (GetAsyncKeyState('D'))
	{
		m_fAngle += 5;
	}
	if (GetAsyncKeyState('W'))
	{
		m_tInfo.vDir = { 0.f, -m_fSpeed, 0.f };

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);
		//대은성은 신이다
		m_tInfo.vPos += m_tInfo.vDir;
	}
	if (GetAsyncKeyState('S'))
	{
		m_tInfo.vDir = { 0.f, +m_fSpeed, 0.f };

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		CObject* pTail = new CCYTail;

		static_cast<CCYTail*>(pTail)->Set_TargetHead(this);

		if (m_TailSegvec.empty())
		{
			pTail->Set_TargetObj(this);
		}
		else
		{
			pTail->Set_TargetObj(m_TailSegvec.back());
		}

		pTail->Initialize();
		m_TailSegvec.push_back(pTail);
	}
	
}
