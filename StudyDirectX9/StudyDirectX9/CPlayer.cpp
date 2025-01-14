#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
}

void CPlayer::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_fSpeed = 10.f;
    m_tInfo.vDir = { 1.f, 0.f, 0.f };
}

void CPlayer::Update()
{
    if (GetAsyncKeyState('W') & 0x8000) // W 키 (위로)
    {
        m_tInfo.vDir = { 0.f, -1.f, 0.f };
        float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
        m_tInfo.vDir.x /= fLength;
        m_tInfo.vDir.y /= fLength;
        m_tInfo.vDir.z = 0.f;

        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

    }
    if (GetAsyncKeyState('S') & 0x8000) // S 키 (아래로)
    {
        m_tInfo.vDir = { 0.f, 1.f, 0.f };
        float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
        m_tInfo.vDir.x /= fLength;
        m_tInfo.vDir.y /= fLength;
        m_tInfo.vDir.z = 0.f;

        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
    }
    if (GetAsyncKeyState('A') & 0x8000) // A 키 (왼쪽으로)
    {
        m_tInfo.vDir = { -1.f, 0.f, 0.f };
        float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
        m_tInfo.vDir.x /= fLength;
        m_tInfo.vDir.y /= fLength;
        m_tInfo.vDir.z = 0.f;

        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
    }
    if (GetAsyncKeyState('D') & 0x8000) // D 키 (오른쪽으로)
    {
        m_tInfo.vDir = { 1.f, 0.f, 0.f };
        float		fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
        m_tInfo.vDir.x /= fLength;
        m_tInfo.vDir.y /= fLength;
        m_tInfo.vDir.z = 0.f;

        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
    }
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CPlayer::Release()
{
}
