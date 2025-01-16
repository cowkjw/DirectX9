#include "pch.h"
#include "CCYTail.h"

void CCYTail::Initialize()
{
	m_eOBJID = OBJ_END;
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_fSpeed = 2.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	CCYObject::Initialize_OriginPoint(12, 10);
}

int CCYTail::Update()
{
	return 0;
}

void CCYTail::Late_Update()
{
}

void CCYTail::Render(HDC hDC)
{
}

void CCYTail::Release()
{
}

void CCYTail::OnCollision(CObject* _obj)
{
}
