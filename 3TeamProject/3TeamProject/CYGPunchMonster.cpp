#include "pch.h"
#include "CYGPunchMonster.h"

CYGPunchMonster::CYGPunchMonster()
{
}

void CYGPunchMonster::Initialize()
{
	m_eOBJID = OBJ_MONSTER;
	m_eRender = RENDER_GAMEOBJECT;
}

int CYGPunchMonster::Update()
{
	__super::Update_Rect();
	return 0;
}

void CYGPunchMonster::Late_Update()
{
}

void CYGPunchMonster::Render(HDC hDC)
{
	ColorCircle(hDC, m_tHitRect.left, m_tHitRect.top , m_tHitRect.right, m_tHitRect.bottom, 252, 194, 114, 2);

}

void CYGPunchMonster::Release()
{
}

void CYGPunchMonster::OnCollision(CObject* _obj)
{
}
