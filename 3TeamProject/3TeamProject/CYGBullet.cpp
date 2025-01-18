#include "pch.h"
#include "CYGBullet.h"
#include "CScrollManager.h"

CYGBullet::CYGBullet():m_iReMoveTick(0)
{
}

CYGBullet::~CYGBullet()
{
}

void CYGBullet::Initialize()
{
	m_eOBJID = OBJ_PLAYERBULLET;
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.fSizeX = 10.f;
	m_tInfo.fSizeY = 10.f;
	m_fSpeed = 10.f;
	m_iReMoveTick = 0;
}

int CYGBullet::Update()
{
	m_iReMoveTick++;

	if (m_iReMoveTick > 100) {
		return OBJ_DEAD;
	}
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	__super::Update_Rect();
	return 0;
}

void CYGBullet::Late_Update()
{
}

void CYGBullet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();
	Rectangle(hDC, m_tHitRect.left+ iScrollX, m_tHitRect.top+ iScrollY, m_tHitRect.right+ iScrollX, m_tHitRect.bottom+ iScrollY);
}

void CYGBullet::Release()
{
}

void CYGBullet::OnCollision(CObject* _obj)
{
}
