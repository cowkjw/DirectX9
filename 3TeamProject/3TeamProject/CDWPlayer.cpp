#include "pch.h"
#include "CDWPlayer.h"

CDWPlayer::CDWPlayer()
{
}

void CDWPlayer::Initialize()
{
    m_eOBJID = OBJ_PLAYER;
    m_eRender = RENDER_GAMEOBJECT;

    m_tInfo.vPos = { 400.f, 500.f, 0.f };
    m_fSpeed = 10.f;
    m_tInfo.vLook = { 1.f, 0.f, 0.f };
    m_fNemoAngel = 0.f;

    m_vCorner[0] = { -400,-400,0 }; // 왼쪽위
    m_vCorner[1] = { 400,-400,0 }; // 오른쪽위
    m_vCorner[2] = { 400,400,0 }; // 오른쪽 아래
    m_vCorner[3] = { -400,400,0 }; // 왼쪽 아래

}

int CDWPlayer::Update()
{
    Key_Input();
    D3DXMatrixRotationZ(&matRotZ, m_fNemoAngel);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
    WorldMat = matRotZ * matTrans;
    for (int i = 0; i < 4; i++)
    {
        D3DXVec3TransformCoord(&transformedCorners[i], &m_vCorner[i], &WorldMat);
    }
    __super::Update_Rect();
    return 0;
}
void CDWPlayer::Key_Input()
{
    if (GetAsyncKeyState('A'))
    {
        m_fNemoAngel -= D3DXToRadian(5.f);
    }
    else if (GetAsyncKeyState('D'))
    {
        m_fNemoAngel += D3DXToRadian(5.f);
    }
    if (GetAsyncKeyState('W'))
    {
        D3DXVECTOR3 tmp = { 0.f,-5.f,0.f };
        D3DXVec3TransformNormal(&m_tInfo.vDir, &tmp, &WorldMat);
        m_tInfo.vPos += m_tInfo.vDir;
    }
    else if (GetAsyncKeyState('S'))
    {
        D3DXVECTOR3 tmp = { 0.f,5.f,0.f };
        D3DXVec3TransformNormal(&m_tInfo.vDir, &tmp, &WorldMat);
        m_tInfo.vPos += m_tInfo.vDir;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        D3DXVECTOR3 tmp = { -5.f,0.f,0.f };
        D3DXVec3TransformNormal(&m_tInfo.vDir, &tmp, &WorldMat);
        m_tInfo.vPos += m_tInfo.vDir;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        D3DXVECTOR3 tmp = { 5.f,0.f,0.f };
        D3DXVec3TransformNormal(&m_tInfo.vDir, &tmp, &WorldMat);
        m_tInfo.vPos += m_tInfo.vDir;
    }
}
void CDWPlayer::Late_Update()
{
}
void CDWPlayer::Render(HDC hDC)
{
    // 플레이어 사각형 렌더링
    MoveToEx(hDC, transformedCorners[0].x, transformedCorners[0].y, nullptr);
    LineTo(hDC, transformedCorners[1].x, transformedCorners[1].y);
    LineTo(hDC, transformedCorners[2].x, transformedCorners[2].y);
    LineTo(hDC, transformedCorners[3].x, transformedCorners[3].y);
    LineTo(hDC, transformedCorners[0].x, transformedCorners[0].y);


    D3DXVECTOR3 Sosil[4] =
    {
        { 350.f, 250.f, 0.f }, // 왼쪽 위
        { 450.f, 250.f, 0.f }, // 오른쪽 위
        { 450.f, 350.f, 0.f }, // 오른쪽 아래
        { 350.f, 350.f, 0.f }  // 왼쪽 아래
    };


    MoveToEx(hDC, Sosil[0].x, Sosil[0].y, nullptr);
    LineTo(hDC, Sosil[1].x, Sosil[1].y);
    LineTo(hDC, Sosil[2].x, Sosil[2].y);
    LineTo(hDC, Sosil[3].x, Sosil[3].y);
    LineTo(hDC, Sosil[0].x, Sosil[0].y);

    for (int i = 0; i < 4; ++i)
    {
        MoveToEx(hDC, transformedCorners[i].x, transformedCorners[i].y, nullptr);
        LineTo(hDC, Sosil[i].x, Sosil[i].y);
    }

    if (g_bDevmode)
    {
        HitCircle(hDC, m_tHitRect, 0, 0);
    }
}



void CDWPlayer::Release()
{
}

void CDWPlayer::OnCollision(CObject* _obj)
{
}
