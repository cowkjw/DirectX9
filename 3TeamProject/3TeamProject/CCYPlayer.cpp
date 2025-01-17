#include "pch.h"
#include "CCYPlayer.h"
#include "CCYObject.h"
#include "CCYTail.h"
#include "Define.h"

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
	CCYObject::Initialize_OriginPoint(12, 16);

}

int CCYPlayer::Update()
{
	Key_Input();




	m_tInfo.vDir = m_tInfo.vPos - Get_Mouse();
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_fTargetAngle = acosf(m_tInfo.vDir.x);

	if (Get_Mouse().y > m_tInfo.vPos.y)
		m_fTargetAngle = (2 * D3DX_PI) - m_fTargetAngle;

	if (abs(m_fTargetAngle - m_fAngle) > D3DX_PI)
	{
		if (m_fAngle < m_fTargetAngle)
		{
			m_fAngle -= D3DXToRadian(2.f);
		}
		else if (m_fAngle > m_fTargetAngle)
		{
			m_fAngle += D3DXToRadian(2.f);
		}
	}
	else
	{
		if (m_fAngle < m_fTargetAngle)
		{
			m_fAngle += D3DXToRadian(2.f);
		}
		else if (m_fAngle > m_fTargetAngle)
		{
			m_fAngle -= D3DXToRadian(2.f);
		}
	}

	if (m_fAngle > 2 * D3DX_PI)
		m_fAngle -= 2 * D3DX_PI;
	else if (m_fAngle < 0)
		m_fAngle += 2 * D3DX_PI;








	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));

	m_tInfo.matWorld = matRotZ * matTrans;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);
	//m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;



	m_tInfo.vPos.x -= cosf(m_fAngle) * m_fSpeed;
	m_tInfo.vPos.y -= sinf(m_fAngle) * m_fSpeed;

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

	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 220, 220));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);


	HBRUSH PinkBrush = CreateSolidBrush(RGB(255, 220, 220));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, PinkBrush);

	Polygon(hDC, m_pRenderPoint, m_vOriginPointvec.size());
	SelectObject(hDC, OldBrush); DeleteObject(PinkBrush);
	SelectObject(hDC, hOldPen); DeleteObject(hPen);

	//Ellipse(hDC, )


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
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		m_fSpeed = 4.f;
	}
	else
	{
		m_fSpeed = 2.f;
	}
	
}



//{
//	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;
//
//	// 벡터의 정규화 : 벡터의 크기를 1로 만드는 과정
//	// 단위 벡터 : 크기가 1인 벡터(정규화가 완료된 벡터)
//
//	// 단위 벡터 = 각각의 좌표에 벡터의 크기를 나눈 값
//	float        fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
//	m_tInfo.vDir.x /= fLength;
//	m_tInfo.vDir.y /= fLength;
//	m_tInfo.vDir.z = 0.f;
//
//	// 단위 벡터인 상황에서 acos(내적)
//	m_fTargetAngle = acosf(m_tInfo.vDir.x);
//	if (m_pPlayer->Get_Info().vPos.y > m_tInfo.vPos.y)
//		m_fTargetAngle = (2 * PI) - m_fTargetAngle;
//
//	if (abs(m_fTargetAngle - m_fAngle) > PI)
//	{
//		if (m_fAngle < m_fTargetAngle)
//		{
//			m_fAngle -= ROTATESPEED;
//		}
//		else if (m_fAngle > m_fTargetAngle)
//		{
//			m_fAngle += ROTATESPEED;
//		}
//	}
//	else
//	{
//		if (m_fAngle < m_fTargetAngle)
//		{
//			m_fAngle += ROTATESPEED;
//		}
//		else if (m_fAngle > m_fTargetAngle)
//		{
//			m_fAngle -= ROTATESPEED;
//		}
//	}
//
//	if (m_fAngle > 2 * PI)
//		m_fAngle -= 2 * PI;
//	else if (m_fAngle < 0)
//		m_fAngle += 2 * PI;
//
//	m_tInfo.vLook.x = cosf(m_fAngle);
//	m_tInfo.vLook.y = -sinf(m_fAngle);
//
//	m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
//
//}