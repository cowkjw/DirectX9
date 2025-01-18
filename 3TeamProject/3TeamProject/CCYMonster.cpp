#include "pch.h"
#include "CCYMonster.h"

void CCYMonster::Initialize()
{
	m_eOBJID = OBJ_MONSTER;
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_fSpeed = 2.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	CCYObject::Initialize_OriginPoint(12, 16);
}

int CCYMonster::Update()
{
    return 0;
}

void CCYMonster::Late_Update()
{
}

void CCYMonster::Render(HDC hDC)
{
}

void CCYMonster::Release()
{
}

void CCYMonster::OnCollision(CObject* _obj)
{
}
