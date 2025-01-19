#include "pch.h"
#include "CYGBulletItem.h"
#include "CScrollManager.h"
#include "CSoundManager.h"

CYGBulletItem::CYGBulletItem()
{
	m_itemType = ITEM_BULLET;
}

CYGBulletItem::~CYGBulletItem()
{
	
}
int CYGBulletItem::Update()
{
	if (m_bDead) {
		CSoundManager::GetInstance()->PlayEffect("YGBulletPickup");
		return OBJ_DEAD;
	}
	__super::Update_Rect();
	return 0;
}

void CYGBulletItem::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

	ColorRect(hDC, m_tHitRect.left + iScrollX, m_tHitRect.top + iScrollY, m_tHitRect.right + iScrollX, m_tHitRect.bottom + iScrollY,12,102,51,2,7,162,75);
	
	CYGItem::Render(hDC);

	if (g_bDevmode) {
		HitRect(hDC, m_tHitRect, iScrollX, iScrollY);
	}
}