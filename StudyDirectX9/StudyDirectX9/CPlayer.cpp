#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer():m_fAngle(0)
{
}

void CPlayer::Initialize()
{
    leftTop = {350.f, 250.f, 0.f};
    rightTop = {450.f, 250.f, 0.f};
    leftBottom = {350.f, 350.f, 0.f};
    rightBottom = {450.f, 350.f, 0.f};

    m_tInfo.vPos = { 400.f, 300.f, 0.f };

	m_fSpeed = 10.f;
}

void CPlayer::Update()
{
    if (GetAsyncKeyState('W') & 0x8000) // W 키 (위로)
    {
        m_tInfo.vDir = { 0.f, -1.f, 0.f };

        D3DXMatrixRotationZ(&m_tInfo.matWorld, D3DXToRadian(m_fAngle+90));
        D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);

        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
        leftTop += m_tInfo.vDir * m_fSpeed;
        rightTop += m_tInfo.vDir * m_fSpeed;
        leftBottom += m_tInfo.vDir * m_fSpeed;
        rightBottom += m_tInfo.vDir * m_fSpeed;

    }
    if (GetAsyncKeyState('S') & 0x8000) // S 키 (아래로)
    {
        m_tInfo.vDir = { 0.f, 1.f, 0.f };
        D3DXMatrixRotationZ(&m_tInfo.matWorld, D3DXToRadian(m_fAngle + 90));
        D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);

        m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
        leftTop += m_tInfo.vDir * m_fSpeed;
        rightTop += m_tInfo.vDir * m_fSpeed;
        leftBottom += m_tInfo.vDir * m_fSpeed;
        rightBottom += m_tInfo.vDir * m_fSpeed;
    }
    if (GetAsyncKeyState('A') & 0x8000) // A 키 (왼쪽으로)
    {
        m_fAngle--;
        D3DXMatrixRotationZ(&m_tInfo.matWorld, D3DXToRadian(-1)); // 각도를 라디안으로 변환

        // 사각형의 각 꼭짓점 좌표에 회전 행렬을 적용
        D3DXVECTOR3 vLeftTop = leftTop - m_tInfo.vPos;
        D3DXVECTOR3 vRightTop = rightTop - m_tInfo.vPos;
        D3DXVECTOR3 vLeftBottom = leftBottom - m_tInfo.vPos;
        D3DXVECTOR3 vRightBottom = rightBottom - m_tInfo.vPos;

        D3DXVec3TransformCoord(&vLeftTop, &vLeftTop, &m_tInfo.matWorld);
        D3DXVec3TransformCoord(&vRightTop, &vRightTop, &m_tInfo.matWorld);
        D3DXVec3TransformCoord(&vLeftBottom, &vLeftBottom, &m_tInfo.matWorld);
        D3DXVec3TransformCoord(&vRightBottom, &vRightBottom, &m_tInfo.matWorld);

        // 회전된 좌표에 원래의 위치를 더하여 최종 좌표 계산
        leftTop = vLeftTop + m_tInfo.vPos;
        rightTop = vRightTop + m_tInfo.vPos;
        leftBottom = vLeftBottom + m_tInfo.vPos;
        rightBottom = vRightBottom + m_tInfo.vPos;
    }
    if (GetAsyncKeyState('D') & 0x8000) // D 키 (오른쪽으로)
    {
        m_fAngle++;

        D3DXMatrixRotationZ(&m_tInfo.matWorld, D3DXToRadian(1)); // 각도를 라디안으로 변환

        // 사각형의 각 꼭짓점 좌표에 회전 행렬을 적용
        D3DXVECTOR3 vLeftTop = leftTop - m_tInfo.vPos;
        D3DXVECTOR3 vRightTop = rightTop - m_tInfo.vPos;
        D3DXVECTOR3 vLeftBottom = leftBottom - m_tInfo.vPos;
        D3DXVECTOR3 vRightBottom = rightBottom - m_tInfo.vPos;

        D3DXVec3TransformCoord(&vLeftTop, &vLeftTop, &m_tInfo.matWorld);
        D3DXVec3TransformCoord(&vRightTop, &vRightTop, &m_tInfo.matWorld);
        D3DXVec3TransformCoord(&vLeftBottom, &vLeftBottom, &m_tInfo.matWorld);
        D3DXVec3TransformCoord(&vRightBottom, &vRightBottom, &m_tInfo.matWorld);

        // 회전된 좌표에 원래의 위치를 더하여 최종 좌표 계산
        leftTop = vLeftTop + m_tInfo.vPos;
        rightTop = vRightTop + m_tInfo.vPos;
        leftBottom = vLeftBottom + m_tInfo.vPos;
        rightBottom = vRightBottom + m_tInfo.vPos;

    }

    float angleInRadians = m_fAngle * (PI / 180.f);
    m_tPosin.x = long(m_tInfo.vPos.x + (100 * cosf(angleInRadians)));
    m_tPosin.y = long(m_tInfo.vPos.y + (100 * sinf(angleInRadians)));
}

void CPlayer::Render(HDC hDC)
{
    MoveToEx(hDC, (int)leftTop.x, (int)leftTop.y, nullptr);
    LineTo(hDC, (int)rightTop.x, (int)rightTop.y);
    LineTo(hDC, (int)rightBottom.x, (int)rightBottom.y);
    LineTo(hDC, (int)leftBottom.x, (int)leftBottom.y);
    LineTo(hDC, (int)leftTop.x, (int)leftTop.y);

    MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
    LineTo(hDC, (int)m_tPosin.x, (int)m_tPosin.y);

    TCHAR szBuffer3[128];
    _stprintf_s(szBuffer3, _T("내적값 : %f"), m_fAngle);
    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkMode(hDC, TRANSPARENT);
    TextOut(hDC, 650, 50, szBuffer3, (int)_tcslen(szBuffer3));
}

void CPlayer::Release()
{
}
