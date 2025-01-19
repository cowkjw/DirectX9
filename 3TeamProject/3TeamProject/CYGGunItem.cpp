#include "pch.h"
#include "CYGGunItem.h"
#include "CScrollManager.h"
#include "CSoundManager.h"

CYGGunItem::CYGGunItem()
{
	m_itemType = ITEM_GUN;
}

CYGGunItem::~CYGGunItem()
{
	
}

int CYGGunItem::Update()
{
	if (m_bDead) {
		CSoundManager::GetInstance()->PlayEffect("YGGunPickup");
		return OBJ_DEAD;
	}
	__super::Update_Rect();
	return 0;
}

void CYGGunItem::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();

	ColorRect(hDC, m_tInfo.vPos.x - 25 + iScrollX, m_tInfo.vPos.y - 15 + iScrollY, m_tInfo.vPos.x + 25 + iScrollX, m_tInfo.vPos.y +iScrollY, 0,0,0,0);
	ColorRect(hDC, m_tInfo.vPos.x +10 + iScrollX, m_tInfo.vPos.y + iScrollY, m_tInfo.vPos.x + 25 + iScrollX, m_tInfo.vPos.y +iScrollY +15, 0,0,0,0);
	MoveToEx(hDC, m_tInfo.vPos.x + iScrollX, m_tInfo.vPos.y + iScrollY, nullptr);
	LineTo(hDC, m_tInfo.vPos.x + iScrollX +3, m_tInfo.vPos.y+7 + iScrollY);
	LineTo(hDC, m_tInfo.vPos.x + iScrollX+10, m_tInfo.vPos.y+7 + iScrollY);

	CYGItem::Render(hDC);

	if (g_bDevmode) {
		HitRect(hDC, m_tHitRect, iScrollX, iScrollY);
	}


}
