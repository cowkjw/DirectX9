#include "pch.h"
#include "CFruit.h"
#include "CKeyManager.h"

CFruit::CFruit() : m_fMass(0.f), m_fRadius(0.f),m_fAngle(0.f), m_eFruitType(FRUIT_TYPE::END)
, m_bDropped(false), m_vVelocity(D3DXVECTOR3(0.f, 0.f, 0.f)), m_bIsGround(false)
{

}

CFruit::CFruit(FRUIT_TYPE eFruitType, float fMass) : m_eFruitType(eFruitType), m_fMass(fMass), m_fAngle(0.f), m_fRadius(0.f),
m_bDropped(false), m_vVelocity(D3DXVECTOR3(0.f, 0.f, 0.f)), m_bIsGround(false)
{

}

void CFruit::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
	Initialize_OriginPoint(15, 30);
	m_bDropped = false;
	m_bIsGround = false;
	m_fSpeed = 3.f;
	m_fMass = 2.f;
	m_tInfo.vPos = { 400.f,50.f,0.f };
	m_vScale = { 1.f,1.f,1.f };
}

int CFruit::Update()
{
	if (!m_bDropped)
	{
		Follow_Mpuse();
	}
	else
	{
		// 중력 적용
		m_vVelocity.y += GRAVITY * 0.15f;

		// 좌우 벽 충돌
		if (m_tInfo.vPos.x - m_fRadius < 0.f)
		{
			m_tInfo.vPos.x = m_fRadius;
			m_vVelocity.x *= -0.5f; // 벽에 부딪힐 때 반발
		}
		else if (m_tInfo.vPos.x + m_fRadius > 800.f) // 화면 가로 크기
		{
			m_tInfo.vPos.x = 800.f - m_fRadius;
			m_vVelocity.x *= -0.5f;
		}

		// 바닥 충돌
		if (m_tInfo.vPos.y + m_fRadius > 500.f) // 바닥 y좌표
		{
			m_tInfo.vPos.y = 500.f - m_fRadius;
			//m_vVelocity.y *= -0.3f; // 바닥 반발력
			//m_vVelocity.x *= 0.95f; // 바닥 마찰

			//if (abs(m_vVelocity.y) < 0.1f)
			//{
			//	m_vVelocity.y = 0.f;
			//	m_bIsGround = true;
			//}
		}

		// 위치 업데이트
		m_tInfo.vPos += m_vVelocity;
	}

	// 회전 효과
	if (D3DXVec3Length(&m_vVelocity) > 0.1f)
	{
		m_fAngle += m_vVelocity.x * 0.5f; // x방향 속도에 따라 회전
	}

	Update_Matrix();

	if (CKeyManager::Get_Instance()->Key_Down('A'))
	{
		m_fAngle -= 5.f;
		m_vScale = { 2.f,2.f,2.f };
		m_fRadius *= 2.f;
	}

	if (CKeyManager::Get_Instance()->Key_Down('D'))
	{
		m_fAngle += 5.f;
		m_vScale = { 1.f,1.f,1.f };
		m_fRadius *=0.5f;
	}

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (!m_bDropped)
		{
			m_bDropped = true;
		}
	}
	if (m_fSpeed > 0.f)
	{
		D3DXVECTOR3 vTangent = D3DXVECTOR3(-m_tInfo.vDir.y, m_tInfo.vDir.x, 0.0f);
		m_tInfo.vPos += vTangent * m_fSpeed;
		m_fAngle += 0.1f * m_fSpeed;

		// 속도 감소
		m_fSpeed *= 0.97f;

		// 최소 속도에서 멈춤
		if (m_fSpeed < 0.01f)
			m_fSpeed = 0.f;
	}

    return 0;
}

void CFruit::Late_Update()
{
}

void CFruit::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vecRenderPoints[0].x, (int)m_vecRenderPoints[0].y, nullptr);
	for (int i = 0; i < (int)m_vecRenderPoints.size(); i++)
	{
		LineTo(hDC, (int)m_vecRenderPoints[i].x, (int)m_vecRenderPoints[i].y);
	}
	LineTo(hDC, (int)m_vecRenderPoints[0].x, (int)m_vecRenderPoints[0].y);

	Ellipse(hDC,
		int(m_vecRenderPoints.back().x - 5.f),
		int(m_vecRenderPoints.back().y - 5.f),
		int(m_vecRenderPoints.back().x + 5.f),
		int(m_vecRenderPoints.back().y + 5.f));
}

void CFruit::Release()
{
}

void CFruit::OnCollision(CObject* _obj)
{
	//if (!_obj || this == _obj) return;
	//CFruit* pFruit = dynamic_cast<CFruit*>(_obj);
	//if (!pFruit) return;

	//// 1. 충돌 방향과 깊이 계산
	//D3DXVECTOR3 vDir = (pFruit->Get_Info().vPos - m_tInfo.vPos);
	//float fDist = D3DXVec3Length(&vDir);
	//D3DXVec3Normalize(&vDir, &vDir);
	//float penetration = pFruit->Get_Radius() + m_fRadius - fDist;
	//float maxPenetration = 10.f; // 최대 보정량
	//penetration = min(penetration, maxPenetration);
	//m_tInfo.vPos -= vDir* penetration;
	////pFruit->Get_Info().vPos += vDir * (penetration);

	////D3DXVECTOR3 vTangent = D3DXVECTOR3(-vDir.y, vDir.x, 0.0f);

	////// 3. 접선 방향으로 이동 + 회전
	////float fMoveSpeed = 2.0f;  // 이동 속도 조절
	////m_tInfo.vPos += vTangent * fMoveSpeed;  // 접선 방향으로 이동

	////float fRotationSpeed = 0.1f;  // 회전 속도 조절
	////m_fAngle += fRotationSpeed * fMoveSpeed;  // 이동 속도에 비례해서 회전
	//m_fSpeed = 2.f;

	if (!_obj || this == _obj) return;
	CFruit* pFruit = dynamic_cast<CFruit*>(_obj);
	if (!pFruit) return;

	// 1. 충돌 방향과 깊이 계산
	D3DXVECTOR3 vDir = (pFruit->Get_Info().vPos - m_tInfo.vPos);
	float fDist = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);

	float penetration = pFruit->Get_Radius() + m_fRadius - fDist;
	float maxPenetration = 10.f;
	penetration = min(penetration, maxPenetration);

	// 양쪽 과일 모두 밀어내기
	m_tInfo.vPos -= vDir * (penetration * 0.5f);
	pFruit->Get_Info().vPos += vDir * (penetration * 0.5f);

	// 2. 충돌 후 속도 계산
	float restitution = 0.3f; // 반발 계수

	// 충돌 시 수직 방향의 속도는 줄이고, 수평 방향으로 힘을 줌
	D3DXVECTOR3 vRelativeVel = m_vVelocity - pFruit->Get_Velocity();
	float impulse = -(1.f + restitution) * D3DXVec3Dot(&vRelativeVel, &vDir);
	impulse /= (1.f / m_fMass + 1.f / pFruit->Get_Mass());

	m_vVelocity += (impulse / m_fMass) * vDir;
	pFruit->Set_Velocity(pFruit->Get_Velocity() - (impulse / pFruit->Get_Mass()) * vDir);
}

void CFruit::Drop()
{
	m_vVelocity.y += GRAVITY * 0.15f;
	m_tInfo.vPos += m_vVelocity * 0.15f;
	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
}

void CFruit::Follow_Mpuse()
{
	POINT		pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	RECT rcClient;
	GetClientRect(g_hWnd, &rcClient);

	// 마우스가 클라이언트 영역 안에 있는지 확인
	if (pt.x >= rcClient.left && pt.x <= rcClient.right &&
		pt.y >= rcClient.top && pt.y <= rcClient.bottom)
	{
		D3DXVECTOR3 vMouse((float)pt.x, (float)pt.y, 0.f);
		m_tInfo.vPos.x = vMouse.x;
		D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	}
}

void CFruit::Update_Matrix()
{
	D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationZ(&m_matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	for (int i = 0; i < (int)m_vecRenderPoints.size(); i++)
	{
		m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;

		// 해당 점 변환
		D3DXVec3TransformCoord(&m_vecRenderPoints[i], &m_vecLocalPoints[i], &m_tInfo.matWorld);
	}
}

void CFruit::Initialize_OriginPoint(int _iCount, float _Radius, float _fStartAngle)
{
	m_vecLocalPoints.reserve(_iCount);
	m_vecRenderPoints.reserve(_iCount);
	m_fRadius = _Radius;

	float fUnitAngle = 360.f / (float)_iCount;
	float CurAngle(0.f);

	for (int i = 0; i < _iCount; ++i)
	{
		CurAngle = D3DXToRadian(_fStartAngle + fUnitAngle * i);
		m_vecLocalPoints.push_back({ _Radius * cosf(CurAngle), _Radius * sinf(CurAngle) , 0.f });
		m_vecRenderPoints.push_back({ _Radius * cosf(CurAngle), _Radius * sinf(CurAngle) , 0.f });
	}
}

