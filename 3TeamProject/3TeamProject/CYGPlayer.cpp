#include "pch.h"
#include "CYGPlayer.h"
#include "CKeyManager.h"

CYGPlayer::CYGPlayer()
{
}

void CYGPlayer::Initialize()
{
	m_eOBJID = OBJ_PLAYER;
	m_eRender = RENDER_GAMEOBJECT;

	m_fSpeed = 3.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	m_PlayerState = PS_GUN;

	m_vLeftNoGunHandPos = { 385.f,270.f,0.f };
	m_vRightNoGunHandPos = { 415.f,270.f,0.f };
	m_vOriginLeftNoGunHand = m_vLeftNoGunHandPos;
	m_vOriginRightNoGunHand = m_vRightNoGunHandPos;

	m_vLeftGunHandPos = {395.f, 240.f, 0.f};
	m_vRightGunHandPos = {405.f, 270.f, 0.f};
	m_vOriginLeftGunHand = m_vLeftGunHandPos;
	m_vOriginRightGunHand = m_vRightGunHandPos;

	m_vGunRectanglePoint[0] = {395.f, 210.f, 0.f};
	m_vGunRectanglePoint[1] = {405.f, 210.f, 0.f};
	m_vGunRectanglePoint[2] = {405.f, 280.f, 0.f};
	m_vGunRectanglePoint[3] = {395.f, 280.f, 0.f};

	for (int i = 0; i < 4; ++i) {
		m_vOriginGunRectanglePoint[i] = m_vGunRectanglePoint[i];
	}

	m_vOriginPos = m_tInfo.vPos;
}

int CYGPlayer::Update()
{
	m_tInfo.vLook = Get_Mouse() - m_tInfo.vPos;
	m_fAngle = D3DXToDegree(atan2f(m_tInfo.vLook.y, m_tInfo.vLook.x));

	if (m_fAngle < 0) {
		m_fAngle += 360;
	}
	m_fAngle += 100;

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle/60);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;


	m_vLeftNoGunHandPos = m_vOriginLeftNoGunHand;
	m_vLeftNoGunHandPos -= {400.f, 300.f, 0.f};
	D3DXVec3TransformCoord(&m_vLeftNoGunHandPos, &m_vLeftNoGunHandPos, &m_tInfo.matWorld);

	m_vRightNoGunHandPos = m_vOriginRightNoGunHand;
	m_vRightNoGunHandPos -= {400.f, 300.f, 0.f};
	D3DXVec3TransformCoord(&m_vRightNoGunHandPos, &m_vRightNoGunHandPos, &m_tInfo.matWorld);

	m_vLeftGunHandPos = m_vOriginLeftGunHand;
	m_vLeftGunHandPos -= {400.f, 300.f, 0.f};
	D3DXVec3TransformCoord(&m_vLeftGunHandPos, &m_vLeftGunHandPos, &m_tInfo.matWorld);

	m_vRightGunHandPos = m_vOriginRightGunHand;
	m_vRightGunHandPos -= {400.f, 300.f, 0.f};
	D3DXVec3TransformCoord(&m_vRightGunHandPos, &m_vRightGunHandPos, &m_tInfo.matWorld);

	for (int i = 0; i < 4; ++i) {
		m_vGunRectanglePoint[i] = m_vOriginGunRectanglePoint[i];
		m_vGunRectanglePoint[i] -= {400.f, 300.f, 0.f};
		D3DXVec3TransformCoord(&m_vGunRectanglePoint[i], &m_vGunRectanglePoint[i], &m_tInfo.matWorld);
	}


	Key_Input();

	__super::Update_Rect();
	return 0;
}

void CYGPlayer::Late_Update()
{
}

void CYGPlayer::Render(HDC hDC)
{
	if (m_PlayerState == PS_NOGUN) {
		Ellipse(hDC, m_vLeftNoGunHandPos.x - 10, m_vLeftNoGunHandPos.y - 10, m_vLeftNoGunHandPos.x + 10, m_vLeftNoGunHandPos.y + 10); // 왼손
		Ellipse(hDC, m_vRightNoGunHandPos.x - 10, m_vRightNoGunHandPos.y - 10, m_vRightNoGunHandPos.x + 10, m_vRightNoGunHandPos.y + 10); // 오른손
	}
	else {
		MoveToEx(hDC, m_vGunRectanglePoint[3].x, m_vGunRectanglePoint[3].y, nullptr);
		for (int i = 0; i < 4; ++i) {
			LineTo(hDC, m_vGunRectanglePoint[i].x, m_vGunRectanglePoint[i].y);
		}

		Ellipse(hDC, m_vLeftGunHandPos.x - 10, m_vLeftGunHandPos.y - 10, m_vLeftGunHandPos.x + 10, m_vLeftGunHandPos.y + 10); // 왼손
		Ellipse(hDC, m_vRightGunHandPos.x - 10, m_vRightGunHandPos.y - 10, m_vRightGunHandPos.x + 10, m_vRightGunHandPos.y + 10); // 오른손
	}

	Ellipse(hDC, m_tHitRect.left, m_tHitRect.top, m_tHitRect.right, m_tHitRect.bottom);


	if (g_bDevmode) {
		HitCircle(hDC, m_tHitRect, 0, 0);
		if (g_bDevmode) {
			TCHAR szWhoScene[64];
			_stprintf_s(szWhoScene, _T("%f 마우스 %f %f"), m_fAngle, Get_Mouse().x, Get_Mouse().y);
			SetTextColor(hDC, RGB(0, 0, 0));
			TextOut(hDC, 350, 10, szWhoScene, _tcslen(szWhoScene));
		}
	}
}

void CYGPlayer::Release()
{
}

void CYGPlayer::OnCollision(CObject* _obj)
{
}

void CYGPlayer::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Pressing('W')) {
		m_tInfo.vDir = { 0.f, -1.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing('S')) {
		m_tInfo.vDir = { 0.f, 1.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing('A')) {
		m_tInfo.vDir = { -1.f, 0.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing('D')) {
		m_tInfo.vDir = { 1.f, 0.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyManager::Get_Instance()->Key_Down('K')) {
		if (m_PlayerState == PS_NOGUN) {
			m_PlayerState = PS_GUN;
		}
		else {
			m_PlayerState = PS_NOGUN;
		}
		
	}

}
