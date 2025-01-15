#include "pch.h"
#include "CMonster.h"

CMonster::CMonster():m_fAngle(0)
{
}

void CMonster::Initialize()
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_fSpeed = 2.f;

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
}

void CMonster::Update()
{
	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;

	float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	
	float aaa = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook); //a와 b 내적 값 구하기
	float a = D3DXVec3Length(&m_tInfo.vDir); // 절대값 a
	float b = D3DXVec3Length(&m_tInfo.vLook); //절대값 b

	//float cos = aaa / (a * b); //cos세타 
	m_fAngle = acosf(aaa) * (180.f / PI); 

	float k = m_tInfo.vDir.x * m_tInfo.vLook.y - m_tInfo.vDir.y * m_tInfo.vLook.x;
	if (k > 0) {
		m_fAngle = 360.0f - m_fAngle;
	}

	float angleInRadians = m_fAngle * (PI / 180.f);
	m_tPosin.x = long(m_tInfo.vPos.x + (100 * cosf(angleInRadians)));
	m_tPosin.y = long(m_tInfo.vPos.y + (100 * sinf(angleInRadians)));
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));

	MoveToEx(hDC, (int)m_tInfo.vPos.x , (int)m_tInfo.vPos.y, nullptr);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);

	TCHAR szBuffer3[128];
	_stprintf_s(szBuffer3, _T("내적값 : %f"), m_fAngle);
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 650, 50, szBuffer3, (int)_tcslen(szBuffer3));
}

void CMonster::Release()
{
}
