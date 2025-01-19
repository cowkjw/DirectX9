#include "pch.h"
#include "CFruit.h"
#include "CKeyManager.h"
#include "CSoundManager.h"

CFruit::CFruit() : m_fMass(0.f), m_fRadius(0.f), m_fAngle(0.f), m_fRollingSpeed(0.f), m_fMergeAnimRatio(0.f), m_tColor(0UL), m_eFruitType(FRUIT_TYPE::FT_END)
, m_bDropped(false), m_vVelocity(D3DXVECTOR3(0.f, 0.f, 0.f)), m_bIsGround(false), m_bCollided(false),m_bInBox(false), m_eFruitSt(FRUIT_STATE::IDLE),
m_bActive(true), m_dwCanMergeCool(0ULL), m_dwMergedTime(0ULL)
{
	m_tInfo.vPos = { 400.f,60.f,0.f };
}

CFruit::CFruit(FRUIT_TYPE eFruitType, float fMass) : m_eFruitType(eFruitType), m_fMass(fMass), m_bInBox(false), m_bActive(true),
m_tColor(0UL), m_fAngle(0.f), m_fRollingSpeed(0.f), m_fRadius(0.f), m_fMergeAnimRatio(0.f), m_eFruitSt(FRUIT_STATE::IDLE),
m_bDropped(false), m_vVelocity(D3DXVECTOR3(0.f, 0.f, 0.f)), m_bIsGround(false), m_bCollided(false), m_dwCanMergeCool(0ULL), m_dwMergedTime(0ULL)
{
	m_tInfo.vPos = { 400.f,60.f,0.f };
}

void CFruit::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
	Set_Mass();
	m_bInBox = false;
	m_bDropped = false;
	m_bIsGround = false;
	m_fSpeed = 3.f;
	m_fMergeAnimRatio = 0.7f;
	m_fAngle = -65.f;
	m_tInfo.vPos = { 400.f,110.f,0.f };
	m_vScale = { 1.f,1.f,1.f };
	m_dwMergedTime = 0ULL;
	m_dwCanMergeCool = 400ULL;
}

int CFruit::Update()
{
	if (m_eFruitSt == FRUIT_STATE::MERGE || m_eFruitSt == FRUIT_STATE::MERGED)
	{
		Set_Active(false);
		return 0;
	}

	if (!m_bDropped)
	{
		Follow_Mpuse();
	}
	else
	{
		if (!m_bIsGround)  // 바닥에 없을 때만 중력 적용
		{
			m_vVelocity.y += GRAVITY * 0.15f;
		}

		if (m_tInfo.vPos.y + m_fRadius * m_vScale.y < 550.f)
		{
			m_bIsGround = false;
		}

		// 왼쪽 벽 충돌
		if (m_tInfo.vPos.x - m_fRadius * m_vScale.x < 50.f)
		{
			float fPenetration = (50.f + m_fRadius * m_vScale.x) - m_tInfo.vPos.x;
			float fMaxPenetration = 30.f; // 너무 깊게 들어가는 경우 제한
			fPenetration = min(fPenetration, fMaxPenetration);

			m_tInfo.vPos.x = 50.f + m_fRadius * m_vScale.x;

			// 반발력을 penetration에 비례하게 적용
			float restitution = 0.2f;
			float velocityScale = fPenetration / fMaxPenetration;
			m_vVelocity.x = abs(m_vVelocity.x) * restitution * velocityScale;
		}
		// 오른쪽 벽 충돌
		else if (m_tInfo.vPos.x + m_fRadius * m_vScale.x > 750.f)
		{
			float fPenetration = m_tInfo.vPos.x - (750.f - m_fRadius * m_vScale.x);
			float fMaxPenetration = 30.f;
			fPenetration = min(fPenetration, fMaxPenetration);

			m_tInfo.vPos.x = 750.f - m_fRadius * m_vScale.x;

			// 반발력을 penetration에 비례하게 적용
			float restitution = 0.2f;
			float velocityScale = fPenetration / fMaxPenetration;
			m_vVelocity.x = -abs(m_vVelocity.x) * restitution * velocityScale;
		}

		// 바닥 충돌
		if (m_tInfo.vPos.y + m_fRadius * m_vScale.y > 550.f)
		{
			float fPenetration = m_tInfo.vPos.y - (550.f - m_fRadius * m_vScale.y);
			float fMaxPenetration = 30.f;
			fPenetration = min(fPenetration, fMaxPenetration);

			m_tInfo.vPos.y = 550.f - m_fRadius * m_vScale.y;

			// 반발력을 penetration에 비례하게 적용
			float restitution = 0.6f;
			float velocityScale = fPenetration / fMaxPenetration;
			m_vVelocity.y = -abs(m_vVelocity.y) * restitution * velocityScale;
			m_vVelocity.x *= 0.5f; // 바닥 마찰

			if (abs(m_vVelocity.y) < 0.5f)
			{
				m_vVelocity.y = 0.f;
				m_bIsGround = true;
			}
		}

		if (m_bIsGround)
		{
			const float FRICTION = 1.f;  // 마찰 계수 (1보다 작을수록 마찰이 강함)
			m_vVelocity.x *= FRICTION;    // x방향 속도 감소

			if (abs(m_vVelocity.x) < 0.01f)
			{
				m_vVelocity.x = 0.f;
				m_fRollingSpeed = 0.f; 
			}
		}
		// 위치 업데이트
		m_tInfo.vPos += m_vVelocity;
	}

	// 회전 효과
	if (m_fRollingSpeed != 0.f)  // 굴러떨어질 때
	{
		m_fAngle -= m_fRollingSpeed * 4.f;  // 회전 속도 적용
	}
	Update_Matrix();

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (!m_bDropped)
		{
			CSoundManager::GetInstance()->PlayEffect("DropSound");
			m_bDropped = true;
		}
	}

	return 0;
}

void CFruit::Late_Update()
{
	if (m_eFruitSt == FRUIT_STATE::COOLDOWN)
	{
		auto dwCur = GetTickCount64();
		if (dwCur - m_dwMergedTime >= m_dwCanMergeCool)
		{
			m_eFruitSt = FRUIT_STATE::IDLE;
			m_fMergeAnimRatio = 1.f;
		}
		else
		{
			m_fMergeAnimRatio = min(m_fMergeAnimRatio + 0.03f, 1.f);
		}
	}
}

void CFruit::Render(HDC hDC)
{
	POINT* points = new POINT[m_vecRenderPoints.size()];
	for (size_t i = 0; i < m_vecRenderPoints.size(); ++i)
	{
		points[i].x = (LONG)m_vecRenderPoints[i].x;
		points[i].y = (LONG)m_vecRenderPoints[i].y;
	}
	HBRUSH hBrush = CreateSolidBrush(m_tColor);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Polygon(hDC, points, (int)m_vecRenderPoints.size());

	MoveToEx(hDC, (int)m_vecRenderPoints[0].x, (int)m_vecRenderPoints[0].y, nullptr);
	for (int i = 0; i < (int)m_vecRenderPoints.size(); i++)
	{
		LineTo(hDC, (int)m_vecRenderPoints[i].x, (int)m_vecRenderPoints[i].y);
	}
	LineTo(hDC, (int)m_vecRenderPoints[0].x, (int)m_vecRenderPoints[0].y);

	Ellipse(hDC,
		int(m_vecRenderPoints.back().x - m_fRadius/1.5f),
		int(m_vecRenderPoints.back().y - m_fRadius /1.5f),
		int(m_vecRenderPoints.back().x + m_fRadius / 1.5f),
		int(m_vecRenderPoints.back().y + m_fRadius / 1.5f));

	if (g_bDevmode)
	{
		TCHAR szDebugInfo[64];
		_stprintf_s(szDebugInfo, _T("%d"), (int)m_eFruitType);
		SetTextColor(hDC, RGB(0, 0, 0));
		TextOut(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, szDebugInfo, _tcslen(szDebugInfo));
	}
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
	delete[] points;
}

void CFruit::Release()
{
}

void CFruit::OnCollision(CObject* _obj)
{
	if (!_obj || this == _obj) return;

	CFruit* pFruit = dynamic_cast<CFruit*>(_obj);
	if (!pFruit) return;
	if (!pFruit->Is_Dropped() || !m_bDropped) return;

	if (pFruit->Get_FruitType() == m_eFruitType
		&& pFruit->Get_State() == FRUIT_STATE::IDLE && m_eFruitSt == FRUIT_STATE::IDLE)
	{
		m_eFruitSt = m_tInfo.vPos.y > pFruit->Get_Info().vPos.y ? FRUIT_STATE::MERGED : FRUIT_STATE::MERGE;
		pFruit->Set_State(m_tInfo.vPos.y > pFruit->Get_Info().vPos.y ? FRUIT_STATE::MERGE : FRUIT_STATE::MERGED);
		return;
	}


	// 1. 충돌 방향과 깊이 계산
	D3DXVECTOR3 vDir = (pFruit->Get_Info().vPos - m_tInfo.vPos);
	float fDist = D3DXVec3Length(&vDir);
	const float EPSILON = 0.0001f;
	if (vDir.y < 0.f && abs(vDir.x) < EPSILON)
	{
		vDir = D3DXVECTOR3(-0.1f, -0.9f, 0.0f); // 살짝 비스듬하게
	
		fDist = 0.005f;
	}
	D3DXVec3Normalize(&vDir, &vDir);

	float fPenetration = (pFruit->Get_Radius() * pFruit->Get_Scale().x + m_fRadius * m_vScale.x) - fDist;
	float fMaxPenetration = 30.f; // 너무 깊게 들어가는 경우 멀리 팅겨져 나감
	fPenetration = min(fPenetration, fMaxPenetration);

	// 양쪽 과일 모두 밀어내기
	float fTotalMass = m_fMass + pFruit->Get_Mass();
	float fMyRatio = pFruit->Get_Mass() / fTotalMass;    // 상대방 질량이 클수록 내가 많이 밀림
	float fOtherRatio = m_fMass / fTotalMass;           // 내 질량이 클수록 상대가 많이 밀림
	// 질량비에 따라 다르게 밀어내기
	m_tInfo.vPos -= vDir * (fPenetration * fMyRatio);
	pFruit->Get_Info().vPos += vDir * (fPenetration * fOtherRatio);

	// 2. 충돌 후 속도 계산
	float restitution = 0.2f; // 반발 계수

	// 충돌 시 수직 방향의 속도는 줄이고, 수평 방향으로 힘을 줌
	D3DXVECTOR3 vRelativeVel = m_vVelocity - pFruit->Get_Velocity(); // 상대 속도 구해줌
	if (m_tInfo.vPos.y < pFruit->Get_Info().vPos.y)
	{
		// 접선 벡터 (vDir이 충돌 시에 법선벡터임)
		D3DXVECTOR3 vTangent;
		vTangent.x = -vDir.y; // ex (3,4,0)과 (-4,3,0)은 수직
		vTangent.y = vDir.x;
		vTangent.z = 0.f;
		float fTangentialVelocity = D3DXVec3Dot(&m_vVelocity, &vTangent); // 전체 속도에서 접선 방향의 속도 구하기 위함

		// 접선 방향 속도를 더 많이 감소시켜 덜 튀게 만들기
		fTangentialVelocity *= 0.8f;

		// 회전 속도
		m_fRollingSpeed = fTangentialVelocity * (6.5f / m_fRadius * m_vScale.x);

		// 수직 방향 반발력을 더 줄임
		float fRollingRestitution = 0.3f;  // 반발 계수 작을 수록 진흙과 같음
		// D3DXVec3Dot(&vRelativeVel, &vDir) 은 충돌방향(법선 방향의 속도 성분)
		float fImpulse = -(1.f + fRollingRestitution) * D3DXVec3Dot(&vRelativeVel, &vDir); // 충격량 -는 충격량을 반대로 주기 위함 1을 더하는 건 운동량 보존 법칙
		fImpulse /= (1.f / m_fMass + 1.f / pFruit->Get_Mass()); // 뉴턴의 운동 법칙 (질량이 같다면 충격량 유지, 한쪽이 무겁다면 충격량이 커짐)
		m_vVelocity = vTangent * fTangentialVelocity + (fImpulse / m_fMass) * vDir; // 접선 방향 속도 + 법선 방향 속도
		pFruit->Set_Velocity(pFruit->Get_Velocity() - (fImpulse / pFruit->Get_Mass()) * vDir);
	}
	else
	{
		m_fRollingSpeed = 0.f;
		// 일반 충돌
		float fImpulse = -(1.f + restitution) * D3DXVec3Dot(&vRelativeVel, &vDir);
		fImpulse /= (1.f / m_fMass + 1.f / pFruit->Get_Mass());
		m_vVelocity += (fImpulse / m_fMass) * vDir;
		pFruit->Set_Velocity(pFruit->Get_Velocity() - (fImpulse / pFruit->Get_Mass()) * vDir);
	}
	m_bCollided = true;
}

void CFruit::Set_LinePassed(bool bPassed)
{
	if (bPassed && !m_bInBox)
	{
		m_bInBox = true;
	}
}

void CFruit::Reset()
{
	Set_Color();
	Set_Mass();
	Set_Radius();
	Set_Scale();
	m_eRender = RENDER_GAMEOBJECT;
	m_eFruitSt = FRUIT_STATE::IDLE;
	Initialize_OriginPoint(60, m_fRadius);
	m_bDropped = false;
	m_bInBox = false;
	m_bIsGround = false;
	m_bCollided = false;
	m_bActive = true;
	m_fSpeed = 3.f;
	m_fMergeAnimRatio = 0.7f;
	m_tInfo.vPos = { 400.f,60.f,0.f };
	m_fRollingSpeed = 0.f;
	m_dwMergedTime = 0ULL;
	m_dwCanMergeCool = 400ULL;
}

void CFruit::Set_Merged_Fruit()
{
	Set_Color();
	Set_Mass();
	Set_Radius();
	Set_Scale();
	m_eRender = RENDER_GAMEOBJECT;
	m_eFruitSt = FRUIT_STATE::COOLDOWN;
	Initialize_OriginPoint(60, m_fRadius);
	m_bDropped = true;
	m_bInBox = true;
	m_bIsGround = true;
	m_bActive = true;
	m_bCollided = false;
	m_fSpeed = 3.f;
	m_fMergeAnimRatio = 0.7f;
	m_dwMergedTime = GetTickCount64();
	m_dwCanMergeCool = 400ULL;
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
	if (m_eFruitSt != FRUIT_STATE::COOLDOWN)
		D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	else
		D3DXMatrixScaling(&m_matScale, m_vScale.x * m_fMergeAnimRatio, m_vScale.y * m_fMergeAnimRatio, m_vScale.z * m_fMergeAnimRatio);
	D3DXMatrixRotationZ(&m_matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;
		D3DXVec3TransformCoordArray(
			&m_vecRenderPoints[0],     // 출력 벡터 배열의 시작 주소
			sizeof(D3DXVECTOR3),       // 출력 벡터 간의 바이트 간격
			&m_vecLocalPoints[0],      // 입력 벡터 배열의 시작 주소
			sizeof(D3DXVECTOR3),       // 입력 벡터 간의 바이트 간격
			&m_tInfo.matWorld,         // 변환 행렬
			(UINT)m_vecRenderPoints.size()   // 변환할 벡터의 개수
		);
	//for (int i = 0; i < (int)m_vecRenderPoints.size(); i++)
	//{
	//	m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;

	//	// 해당 점 변환
	//	D3DXVec3TransformCoord(&m_vecRenderPoints[i], &m_vecLocalPoints[i], &m_tInfo.matWorld);
	//}
}

void CFruit::Set_Scale()
{
	switch (m_eFruitType)
	{
	case FRUIT_TYPE::CHERRY:
		m_vScale = { 5.f,5.f,5.f };
		break;
	case FRUIT_TYPE::ORANGE:
		m_vScale = { 2.f,2.f,2.f };
		break;
	case FRUIT_TYPE::LEMON:
		m_vScale = { 2.f,2.f,2.f };
		break;
	case FRUIT_TYPE::APPLE:
		m_vScale = { 2.f,2.f,2.f };
		break;
	case FRUIT_TYPE::PEACH:
		m_vScale = { 2.f,2.f,2.f };
		break;
	case FRUIT_TYPE::PINEAPPLE:
		m_vScale = { 2.f,2.f,2.f };
		break;
	case FRUIT_TYPE::MELON:
		m_vScale = { 2.f,2.f,2.f };
		break;
	case FRUIT_TYPE::PUMPKIN:
		m_vScale = { 2.f,2.f,2.f };
		break;
	case FRUIT_TYPE::WATERMELON:
		m_vScale = { 2.3f, 2.3f, 2.3f };
		break;
	case FRUIT_TYPE::FT_END:
	default:
		break;
	}
}

void CFruit::Set_Mass()
{
	switch (m_eFruitType)
	{
	case FRUIT_TYPE::CHERRY:
		m_fMass = 30.f;        // 가장 가벼움
		break;
	case FRUIT_TYPE::ORANGE:
		m_fMass = 50.f;        // 기존 값 유지
		break;
	case FRUIT_TYPE::LEMON:
		m_fMass = 100.f;       // 기존 값 유지
		break;
	case FRUIT_TYPE::APPLE:
		m_fMass = 150.f;      // 기존 값 유지
		break;
	case FRUIT_TYPE::PEACH:
		m_fMass = 300.f;      // 새로운 중간 크기
		break;
	case FRUIT_TYPE::PINEAPPLE:
		m_fMass = 400.f;      // 큰 과일
		break;
	case FRUIT_TYPE::MELON:
		m_fMass = 500.f;      // 더 큰 과일
		break;
	case FRUIT_TYPE::PUMPKIN:
		m_fMass = 500.f;      // 수박 바로 전 크기
		break;
	case FRUIT_TYPE::WATERMELON:
		m_fMass = 600.f;      // 최대 크기 유지
		break;
	case FRUIT_TYPE::FT_END:
	default:
		break;
	}
}

void CFruit::Set_Radius()
{
	switch (m_eFruitType)
	{
	case FRUIT_TYPE::CHERRY:
		m_fRadius = 3.f;
		break;
	case FRUIT_TYPE::ORANGE:
		m_fRadius = 10.f;
		break;
	case FRUIT_TYPE::LEMON:
		m_fRadius = 15.f;
		break;
	case FRUIT_TYPE::APPLE:
		m_fRadius = 30.f;
		break;
	case FRUIT_TYPE::PEACH:
		m_fRadius = 35.f;
		break;
	case FRUIT_TYPE::PINEAPPLE:
		m_fRadius = 40.f;
		break;
	case FRUIT_TYPE::MELON:
		m_fRadius = 50.f;
		break;
	case FRUIT_TYPE::PUMPKIN:
		m_fRadius = 60.f;
		break;
	case FRUIT_TYPE::WATERMELON:
		m_fRadius = 70.f;      // 최대 크기 유지
		break;
	case FRUIT_TYPE::FT_END:
	default:
		break;
	}
}

void CFruit::Set_Color()
{
	switch (m_eFruitType)
	{
	case FRUIT_TYPE::CHERRY:
		m_tColor = RGB(145, 0, 35);     // 더 진한 체리레드
		break;
	case FRUIT_TYPE::ORANGE:
		m_tColor = RGB(255, 140, 0);    // 선명한 오렌지
		break;
	case FRUIT_TYPE::LEMON:
		m_tColor = RGB(255, 231, 0);    // 밝은 레몬 옐로우
		break;
	case FRUIT_TYPE::APPLE:
		m_tColor = RGB(255, 0, 0);      // 순수한 레드
		break;
	case FRUIT_TYPE::PEACH:
		m_tColor = RGB(255, 229, 180);  // 밝은 피치
		break;
	case FRUIT_TYPE::PINEAPPLE:
		m_tColor = RGB(255, 186, 0);    // 황금빛 노란색
		break;
	case FRUIT_TYPE::MELON:
		m_tColor = RGB(120, 255, 140);  // 밝은 연두색
		break;
	case FRUIT_TYPE::PUMPKIN:
		m_tColor = RGB(255, 100, 0);    // 진한 주황색
		break;
	case FRUIT_TYPE::WATERMELON:
		m_tColor = RGB(0, 180, 0);      // 짙은 녹색
		break;
	default:
		m_tColor = RGB(160, 160, 160);  // 회색
		break;
	}
}

void CFruit::Initialize_OriginPoint(int _iCount, float _Radius, float _fStartAngle)
{
	m_vecLocalPoints.clear();
	m_vecRenderPoints.clear();
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

