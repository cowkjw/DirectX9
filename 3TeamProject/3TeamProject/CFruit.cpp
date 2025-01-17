#include "pch.h"
#include "CFruit.h"
#include "CKeyManager.h"

CFruit::CFruit() : m_fMass(0.f), m_fRadius(0.f),m_fAngle(0.f), m_fRollingSpeed (0.f), m_eFruitType(FRUIT_TYPE::END)
, m_bDropped(false), m_vVelocity(D3DXVECTOR3(0.f, 0.f, 0.f)), m_bIsGround(false)
{

}

CFruit::CFruit(FRUIT_TYPE eFruitType, float fMass) : m_eFruitType(eFruitType), m_fMass(fMass), m_fAngle(0.f), m_fRollingSpeed (0.f), m_fRadius(0.f),
m_bDropped(false), m_vVelocity(D3DXVECTOR3(0.f, 0.f, 0.f)), m_bIsGround(false)
{

}

void CFruit::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
	Set_Mass();
	m_bDropped = false;
	m_bIsGround = false;
	m_fSpeed = 3.f;
	m_fMass = 2.f;
	m_fAngle = -65.f;
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
		if (!m_bIsGround)  // �ٴڿ� ���� ���� �߷� ����
		{
			m_vVelocity.y += GRAVITY * 0.15f;
		}

		if (m_tInfo.vPos.y + m_fRadius < 550.f)
		{
			m_bIsGround = false;
		}

		// �¿� �� �浹
		if (m_tInfo.vPos.x - m_fRadius < 50.f)
		{
			m_tInfo.vPos.x = m_fRadius+50.f;
			m_vVelocity.x *= -0.1f; // ���� �ε��� �� �ݹ�
		}
		else if (m_tInfo.vPos.x + m_fRadius > 750.f) // ȭ�� ���� ũ��
		{
			m_tInfo.vPos.x = 750.f - m_fRadius;
			m_vVelocity.x *= -0.1f;
		}

		// �ٴ� �浹
		if (m_tInfo.vPos.y + m_fRadius > 550.f) // �ٴ� y��ǥ
		{
			m_tInfo.vPos.y = 550.f - m_fRadius;
			m_vVelocity.y *= -0.1f; // �ٴ� �ݹ߷�
			m_vVelocity.x *= 0.5f; // �ٴ� ����

			if (abs(m_vVelocity.y) < 0.5f)
			{
				m_vVelocity.y = 0.f;
				m_bIsGround = true;
			}
		}

		// ��ġ ������Ʈ
		m_tInfo.vPos += m_vVelocity;
	}

	// ȸ�� ȿ��
	if (m_fRollingSpeed != 0.f)  // ���������� ��
	{
		m_fAngle -= m_fRollingSpeed*4.f;  // ȸ�� �ӵ� ����
	}
	Update_Matrix();

	if (CKeyManager::Get_Instance()->Key_Down('A'))
	{
		m_fAngle -= 5.f;
		m_vScale = { 2.f,2.f,2.f };
		m_fRadius *= 2.f;
		m_fMass *= 2.f;
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

    return 0;
}

void CFruit::Late_Update()
{
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
		int(m_vecRenderPoints.back().x - 5.f),
		int(m_vecRenderPoints.back().y - 5.f),
		int(m_vecRenderPoints.back().x + 5.f),
		int(m_vecRenderPoints.back().y + 5.f));
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

	// 1. �浹 ����� ���� ���
	D3DXVECTOR3 vDir = (pFruit->Get_Info().vPos - m_tInfo.vPos);
	float fDist = D3DXVec3Length(&vDir);

	D3DXVec3Normalize(&vDir, &vDir);

	float fPenetration = pFruit->Get_Radius() + m_fRadius - fDist;
	float fMaxPenetration = 10.f; // �ʹ� ��� ���� ��� �ָ� �ð��� ����
	fPenetration = min(fPenetration, fMaxPenetration);

	// ���� ���� ��� �о��
	float fTotalMass = m_fMass + pFruit->Get_Mass();
	float fMyRatio = pFruit->Get_Mass() / fTotalMass;    // ���� ������ Ŭ���� ���� ���� �и�
	float fOtherRatio = m_fMass / fTotalMass;           // �� ������ Ŭ���� ��밡 ���� �и�
	// ������ ���� �ٸ��� �о��
	m_tInfo.vPos -= vDir * (fPenetration * fMyRatio);
	pFruit->Get_Info().vPos += vDir * (fPenetration * fOtherRatio);

	// 2. �浹 �� �ӵ� ���
	float restitution = 0.1f; // �ݹ� ���

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
		fTangentialVelocity *= 0.5f;

		// ȸ�� �ӵ�
		m_fRollingSpeed = fTangentialVelocity * (8.f / m_fRadius); 

		// ���� ���� �ݹ߷��� �� ����
		float fRollingRestitution = 0.02f;  // �ݹ� ��� ���� ���� ����� ����
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

void CFruit::Reset()
{
	Set_Color();
	Set_Mass();
	Set_Radius();
	m_eRender = RENDER_GAMEOBJECT;
	Initialize_OriginPoint(60, m_fRadius);
	m_bDropped = false;
	m_bIsGround = false;
	m_fSpeed = 3.f;
	m_fMass = 2.f;
	m_tInfo.vPos = { 400.f,50.f,0.f };
	m_vScale = { 1.f,1.f,1.f };
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
	D3DXMatrixScaling(&m_matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationZ(&m_matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	for (int i = 0; i < (int)m_vecRenderPoints.size(); i++)
	{
		m_tInfo.matWorld = m_matScale * m_matRotZ * m_matTrans;

		// �ش� �� ��ȯ
		D3DXVec3TransformCoord(&m_vecRenderPoints[i], &m_vecLocalPoints[i], &m_tInfo.matWorld);
	}
}

void CFruit::Set_Mass()
{
	  switch (m_eFruitType)
    {
    case FRUIT_TYPE::ORANGE:
        m_fMass = 2.f;
        break;
    case FRUIT_TYPE::LEMON:
        m_fMass = 30.f;      // 4->6
        break;
    case FRUIT_TYPE::APPLE:
        m_fMass = 150.f;     // 8->15
        break;
    case FRUIT_TYPE::WATERMELON:
        m_fMass = 400.f;     // 16->40
        break;
    case FRUIT_TYPE::END:
    default:
        break;
    }
}

void CFruit::Set_Radius()
{
	switch (m_eFruitType)
	{
	case FRUIT_TYPE::ORANGE:
		m_fRadius = 10.f;
		break;
	case FRUIT_TYPE::LEMON:
		m_fRadius = 15.f;
		break;
	case FRUIT_TYPE::APPLE:
		m_fRadius = 30.f;
		break;
	case FRUIT_TYPE::WATERMELON:
		m_fRadius = 60.f;
		break;
	case FRUIT_TYPE::END:
	default:
		break;
	}
}

void CFruit::Set_Color()
{
	switch (m_eFruitType)
	{
	case FRUIT_TYPE::ORANGE:
		m_tColor = RGB(255, 165, 0);  // ��Ȳ��
		break;
	case FRUIT_TYPE::LEMON:
		m_tColor = RGB(200, 200, 0);  // �����
		break;
	case FRUIT_TYPE::APPLE:
		m_tColor = RGB(200, 0, 0);    // ������
		break;
	case FRUIT_TYPE::WATERMELON:
		m_tColor = RGB(0, 200, 0);    // �ʷϻ�
		break;
	default:
		m_tColor = RGB(200, 200, 200);  // �⺻ ȸ��
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

