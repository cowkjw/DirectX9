#include "pch.h"
#include "CYGMonster.h"

CYGMonster::CYGMonster()
{
}

void CYGMonster::Initialize()
{
	m_eOBJID = OBJ_MONSTER;
	m_eRender = RENDER_GAMEOBJECT;
}

int CYGMonster::Update()
{
	__super::Update_Rect();
	return 0;
}

void CYGMonster::Late_Update()
{
}

void CYGMonster::Render(HDC hDC)
{
	ColorCircle(hDC, m_tHitRect.left, m_tHitRect.top , m_tHitRect.right, m_tHitRect.bottom, 252, 194, 114, 2);

}

void CYGMonster::Release()
{
}

void CYGMonster::OnCollision(CObject* _obj)
{
}
