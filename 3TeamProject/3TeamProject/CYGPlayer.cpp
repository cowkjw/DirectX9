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

	leftHandPos = { 380.f,280.f,0.f };
	rightHandPos = { 420.f,280.f,0.f };

	m_vOriginPos = m_tInfo.vPos;
	m_vOriginLeftHand = leftHandPos;
	m_vOriginRightHand = rightHandPos;
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


	leftHandPos = m_vOriginLeftHand;
	leftHandPos -= {400.f, 300.f, 0.f};
	D3DXVec3TransformCoord(&leftHandPos, &leftHandPos, &m_tInfo.matWorld);

	rightHandPos = m_vOriginRightHand;
	rightHandPos -= {400.f, 300.f, 0.f};
	D3DXVec3TransformCoord(&rightHandPos, &rightHandPos, &m_tInfo.matWorld);


	Key_Input();

	__super::Update_Rect();
	return 0;
}

void CYGPlayer::Late_Update()
{
}

void CYGPlayer::Render(HDC hDC)
{
	Ellipse(hDC, m_tHitRect.left, m_tHitRect.top, m_tHitRect.right, m_tHitRect.bottom);
	
	Ellipse(hDC, leftHandPos.x-10, leftHandPos.y - 10, leftHandPos.x + 10, leftHandPos.y + 10); // 왼손
	Ellipse(hDC, rightHandPos.x - 10, rightHandPos.y - 10, rightHandPos.x + 10, rightHandPos.y + 10); // 오른손

	//MoveToEx(hDC, 380, 280, nullptr);
	//LineTo(hDC, leftHandPos.x, leftHandPos.y);

	if (g_bDevmode) {
		HitCircle(hDC, m_tHitRect, 0, 0);
		if (g_bDevmode) {
			TCHAR szWhoScene[64];
			_stprintf_s(szWhoScene, _T("%f 마우스 %f %f"), m_fAngle, Get_Mouse().x, Get_Mouse().y);
			SetTextColor(hDC, RGB(0, 0, 0));
			//SetBkMode(hDC, TRANSPARENT);
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
		leftHandPos += m_tInfo.vDir * m_fSpeed;
		rightHandPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing('S')) {
		m_tInfo.vDir = { 0.f, 1.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		leftHandPos += m_tInfo.vDir * m_fSpeed;
		rightHandPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing('A')) {
		m_tInfo.vDir = { -1.f, 0.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		leftHandPos += m_tInfo.vDir * m_fSpeed;
		rightHandPos += m_tInfo.vDir * m_fSpeed;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing('D')) {
		m_tInfo.vDir = { 1.f, 0.f, 0.f };
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		leftHandPos += m_tInfo.vDir * m_fSpeed;
		rightHandPos += m_tInfo.vDir * m_fSpeed;
	}

}
