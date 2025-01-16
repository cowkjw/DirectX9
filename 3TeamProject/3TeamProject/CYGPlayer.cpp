#include "pch.h"
#include "CYGPlayer.h"

CYGPlayer::CYGPlayer()
{
}

void CYGPlayer::Initialize()
{
	m_eOBJID = OBJ_PLAYER;
	m_eRender = RENDER_GAMEOBJECT;
}

int CYGPlayer::Update()
{
	__super::Update_Rect();
	return 0;
}

void CYGPlayer::Late_Update()
{
}

void CYGPlayer::Render(HDC hDC)
{
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
