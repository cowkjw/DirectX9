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
}

int CYGPlayer::Update()
{
	Key_Input();

	__super::Update_Rect();


	m_tInfo.vDir = m_tInfo.vPos - Get_Mouse();
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	leftHandPos = m_tInfo.vPos + m_tInfo.vDir;
	rightHandPos = m_tInfo.vPos + m_tInfo.vDir;


	return 0;
}

void CYGPlayer::Late_Update()
{
}

void CYGPlayer::Render(HDC hDC)
{
	Ellipse(hDC, m_tHitRect.left, m_tHitRect.top, m_tHitRect.right, m_tHitRect.bottom);
	Ellipse(hDC, leftHandPos.x, leftHandPos.y - 10, leftHandPos.x + 20, leftHandPos.y + 10); // ¿Þ¼Õ
	Ellipse(hDC, rightHandPos.x - 20, rightHandPos.y - 10, rightHandPos.x, rightHandPos.y + 10); // ¿À¸¥¼Õ


	if (g_bDevmode) {
		HitCircle(hDC, m_tHitRect, 0, 0);
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
}
