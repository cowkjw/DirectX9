#include "pch.h"
#include "CFruit.h"
#include "CKeyManager.h"
#include "CSoundManager.h"

CFruit::CFruit() : m_fMass(0.f), m_fRadius(0.f), m_fAngle(0.f), m_fRollingSpeed(0.f), m_fMergeAnimRatio(0.f), m_tColor(0UL), m_eFruitType(FRUIT_TYPE::FT_END)
, m_bDropped(false), m_vVelocity(D3DXVECTOR3(0.f, 0.f, 0.f)), m_bIsGround(false), m_bInBox(false), m_eFruitSt(FRUIT_STATE::IDLE),
m_bActive(true), m_dwCanMergeCool(0ULL), m_dwMergedTime(0ULL)
{
	m_tInfo.vPos = { 400.f,60.f,0.f };
}

CFruit::CFruit(FRUIT_TYPE eFruitType, float fMass) : m_eFruitType(eFruitType), m_fMass(fMass), m_bInBox(false), m_bActive(true),
m_tColor(0UL), m_fAngle(0.f), m_fRollingSpeed(0.f), m_fRadius(0.f), m_fMergeAnimRatio(0.f), m_eFruitSt(FRUIT_STATE::IDLE),
m_bDropped(false), m_vVelocity(D3DXVECTOR3(0.f, 0.f, 0.f)), m_bIsGround(false), m_dwCanMergeCool(0ULL), m_dwMergedTime(0ULL)
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
		if (!m_bIsGround)  // �ٴڿ� ���� ���� �߷� ����
		{
			m_vVelocity.y += GRAVITY * 0.15f;
		}

		if (m_tInfo.vPos.y + m_fRadius * m_vScale.y < 550.f)
		{
			m_bIsGround = false;
		}

		// ���� �� �浹
		if (m_tInfo.vPos.x - m_fRadius * m_vScale.x < 50.f)
		{
			float fPenetration = (50.f + m_fRadius * m_vScale.x) - m_tInfo.vPos.x;
			float fMaxPenetration = 30.f; // �ʹ� ��� ���� ��� ����
			fPenetration = min(fPenetration, fMaxPenetration);

			m_tInfo.vPos.x = 50.f + m_fRadius * m_vScale.x;

			// �ݹ߷��� penetration�� ����ϰ� ����
			float restitution = 0.2f;
			float velocityScale = fPenetration / fMaxPenetration;
			m_vVelocity.x = abs(m_vVelocity.x) * restitution * velocityScale;
		}
		// ������ �� �浹
		else if (m_tInfo.vPos.x + m_fRadius * m_vScale.x > 750.f)
		{
			float fPenetration = m_tInfo.vPos.x - (750.f - m_fRadius * m_vScale.x);
			float fMaxPenetration = 30.f;
			fPenetration = min(fPenetration, fMaxPenetration);

			m_tInfo.vPos.x = 750.f - m_fRadius * m_vScale.x;

			// �ݹ߷��� penetration�� ����ϰ� ����
			float restitution = 0.2f;
			float velocityScale = fPenetration / fMaxPenetration;
			m_vVelocity.x = -abs(m_vVelocity.x) * restitution * velocityScale;
		}

		// �ٴ� �浹
		if (m_tInfo.vPos.y + m_fRadius * m_vScale.y > 550.f)
		{
			float fPenetration = m_tInfo.vPos.y - (550.f - m_fRadius * m_vScale.y);
			float fMaxPenetration = 30.f;
			fPenetration = min(fPenetration, fMaxPenetration);

			m_tInfo.vPos.y = 550.f - m_fRadius * m_vScale.y;

			// �ݹ߷��� penetration�� ����ϰ� ����
			float restitution = 0.2f;
			float velocityScale = fPenetration / fMaxPenetration;
			m_vVelocity.y = -abs(m_vVelocity.y) * restitution * velocityScale;
			m_vVelocity.x *= 0.5f; // �ٴ� ����

			if (abs(m_vVelocity.y) < 0.5f)
			{
				m_vVelocity.y = 0.f;
				m_bIsGround = true;
			}
		}

		if (m_bIsGround)
		{
			const float FRICTION = 1.f;  // ���� ��� (1���� �������� ������ ����)
			m_vVelocity.x *= FRICTION;    // x���� �ӵ� ����

			if (abs(m_vVelocity.x) < 0.01f)
			{
				m_vVelocity.x = 0.f;
				m_fRollingSpeed = 0.f; 
			}
		}
		// ��ġ ������Ʈ
		m_tInfo.vPos += m_vVelocity;
	}

	// ȸ�� ȿ��
	if (m_fRollingSpeed != 0.f)  // ���������� ��
	{
		m_fAngle -= m_fRollingSpeed * 4.f;  // ȸ�� �ӵ� ����
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

			m_fMergeAnimRatio = min(m_fMergeAnimRatio + 0.05f, 1.f);
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


	// 1. �浹 ����� ���� ���
	D3DXVECTOR3 vDir = (pFruit->Get_Info().vPos - m_tInfo.vPos);
	float fDist = D3DXVec3Length(&vDir);
	const float EPSILON = 0.0001f;
	if (vDir.y < 0.f && abs(vDir.x) < EPSILON)
	{
		vDir = D3DXVECTOR3(-0.1f, -0.9f, 0.0f); // ��¦ �񽺵��ϰ�
	
		fDist = 0.005f;
	}
	D3DXVec3Normalize(&vDir, &vDir);

	float fPenetration = (pFruit->Get_Radius() * pFruit->Get_Scale().x + m_fRadius * m_vScale.x) - fDist;
	float fMaxPenetration = 30.f; // �ʹ� ��� ���� ��� �ָ� �ð��� ����
	fPenetration = min(fPenetration, fMaxPenetration);

	// ���� ���� ��� �о��
	float fTotalMass = m_fMass + pFruit->Get_Mass();
	float fMyRatio = pFruit->Get_Mass() / fTotalMass;    // ���� ������ Ŭ���� ���� ���� �и�
	float fOtherRatio = m_fMass / fTotalMass;           // �� ������ Ŭ���� ��밡 ���� �и�
	// ������ ���� �ٸ��� �о��
	m_tInfo.vPos -= vDir * (fPenetration * fMyRatio);
	pFruit->Get_Info().vPos += vDir * (fPenetration * fOtherRatio);

	// 2. �浹 �� �ӵ� ���
	float restitution = 0.2f; // �ݹ� ���

	// �浹 �� ���� ������ �ӵ��� ���̰�, ���� �������� ���� ��
	D3DXVECTOR3 vRelativeVel = m_vVelocity - pFruit->Get_Velocity(); // ��� �ӵ� ������
	if (m_tInfo.vPos.y < pFruit->Get_Info().vPos.y)
	{
		// ���� ���� (vDir�� �浹 �ÿ� ����������)
		D3DXVECTOR3 vTangent;
		vTangent.x = -vDir.y; // ex (3,4,0)�� (-4,3,0)�� ����
		vTangent.y = vDir.x;
		vTangent.z = 0.f;
		float fTangentialVelocity = D3DXVec3Dot(&m_vVelocity, &vTangent); // ��ü �ӵ����� ���� ������ �ӵ� ���ϱ� ����

		// ���� ���� �ӵ��� �� ���� ���ҽ��� �� Ƣ�� �����
		fTangentialVelocity *= 0.8f;

		// ȸ�� �ӵ�
		m_fRollingSpeed = fTangentialVelocity * (6.5f / m_fRadius * m_vScale.x);

		// ���� ���� �ݹ߷��� �� ����
		float fRollingRestitution = 0.3f;  // �ݹ� ��� ���� ���� ����� ����
		// D3DXVec3Dot(&vRelativeVel, &vDir) �� �浹����(���� ������ �ӵ� ����)
		float fImpulse = -(1.f + fRollingRestitution) * D3DXVec3Dot(&vRelativeVel, &vDir); // ��ݷ� -�� ��ݷ��� �ݴ�� �ֱ� ���� 1�� ���ϴ� �� ��� ���� ��Ģ
		fImpulse /= (1.f / m_fMass + 1.f / pFruit->Get_Mass()); // ������ � ��Ģ (������ ���ٸ� ��ݷ� ����, ������ ���̴ٸ� ��ݷ��� Ŀ��)
		m_vVelocity = vTangent * fTangentialVelocity + (fImpulse / m_fMass) * vDir; // ���� ���� �ӵ� + ���� ���� �ӵ�
		pFruit->Set_Velocity(pFruit->Get_Velocity() - (fImpulse / pFruit->Get_Mass()) * vDir);
	}
	else
	{
		m_fRollingSpeed = 0.f;
		// �Ϲ� �浹
		float fImpulse = -(1.f + restitution) * D3DXVec3Dot(&vRelativeVel, &vDir);
		fImpulse /= (1.f / m_fMass + 1.f / pFruit->Get_Mass());
		m_vVelocity += (fImpulse / m_fMass) * vDir;
		pFruit->Set_Velocity(pFruit->Get_Velocity() - (fImpulse / pFruit->Get_Mass()) * vDir);
	}
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

	// ���콺�� Ŭ���̾�Ʈ ���� �ȿ� �ִ��� Ȯ��
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

	for (int i = 0; i < (int)m_vecRenderPoints.size(); i++)
	{
		m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;

		// �ش� �� ��ȯ
		D3DXVec3TransformCoord(&m_vecRenderPoints[i], &m_vecLocalPoints[i], &m_tInfo.matWorld);
	}
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
		m_fMass = 30.f;        // ���� ������
		break;
	case FRUIT_TYPE::ORANGE:
		m_fMass = 50.f;        // ���� �� ����
		break;
	case FRUIT_TYPE::LEMON:
		m_fMass = 100.f;       // ���� �� ����
		break;
	case FRUIT_TYPE::APPLE:
		m_fMass = 150.f;      // ���� �� ����
		break;
	case FRUIT_TYPE::PEACH:
		m_fMass = 300.f;      // ���ο� �߰� ũ��
		break;
	case FRUIT_TYPE::PINEAPPLE:
		m_fMass = 400.f;      // ū ����
		break;
	case FRUIT_TYPE::MELON:
		m_fMass = 500.f;      // �� ū ����
		break;
	case FRUIT_TYPE::PUMPKIN:
		m_fMass = 500.f;      // ���� �ٷ� �� ũ��
		break;
	case FRUIT_TYPE::WATERMELON:
		m_fMass = 600.f;      // �ִ� ũ�� ����
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
		m_fRadius = 70.f;      // �ִ� ũ�� ����
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
		m_tColor = RGB(150, 0, 0);    // ���� ������
		break;
	case FRUIT_TYPE::ORANGE:
		m_tColor = RGB(255, 165, 0);  // ���� ��Ȳ��
		break;
	case FRUIT_TYPE::LEMON:
		m_tColor = RGB(200, 200, 0);  // ���� �����
		break;
	case FRUIT_TYPE::APPLE:
		m_tColor = RGB(200, 0, 0);    // ���� ������
		break;
	case FRUIT_TYPE::PEACH:
		m_tColor = RGB(255, 218, 185); // �����ƻ�
		break;
	case FRUIT_TYPE::PINEAPPLE:
		m_tColor = RGB(255, 223, 0);   // ��翻�ο�
		break;
	case FRUIT_TYPE::MELON:
		m_tColor = RGB(152, 251, 152); // ���� ���
		break;
	case FRUIT_TYPE::PUMPKIN:
		m_tColor = RGB(255, 140, 0);   // ���� ��Ȳ��
		break;
	case FRUIT_TYPE::WATERMELON:
		m_tColor = RGB(0, 200, 0);    // ���� �ʷϻ�
		break;
	default:
		m_tColor = RGB(200, 200, 200); // �⺻ ȸ��
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

