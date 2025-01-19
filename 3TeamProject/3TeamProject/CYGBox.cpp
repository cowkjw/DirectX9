#include "pch.h"
#include "CYGBox.h"
#include "CObjectManager.h"
#include "CYGPlayer.h"
#include "CYGBulletItem.h"
#include "CYGGunItem.h"
#include "CAbstractFactory.h"
#include "CScrollManager.h"
#include "CYGMonster.h"

CYGBox::CYGBox():m_HitTick(0), m_iScaleSize(0)
{
}

CYGBox::~CYGBox()
{
}

void CYGBox::Initialize()
{
	m_eOBJID = OBJ_MAP;
	m_eRender = RENDER_GAMEOBJECT;

	m_vOutBox[0] = { m_tInfo.vPos.x - 35, m_tInfo.vPos.y - 35,0.f };
	m_vOutBox[1] = { m_tInfo.vPos.x + 35, m_tInfo.vPos.y - 35, 0.f };
	m_vOutBox[2] = { m_tInfo.vPos.x + 35, m_tInfo.vPos.y + 35, 0.f };
	m_vOutBox[3] = { m_tInfo.vPos.x - 35, m_tInfo.vPos.y + 35, 0.f };

	m_vInBox[0] = { m_tInfo.vPos.x - 20, m_tInfo.vPos.y - 20, 0.f };
	m_vInBox[1] = { m_tInfo.vPos.x + 20, m_tInfo.vPos.y - 20, 0.f };
	m_vInBox[2] = { m_tInfo.vPos.x + 20, m_tInfo.vPos.y + 20, 0.f };
	m_vInBox[3] = { m_tInfo.vPos.x - 20, m_tInfo.vPos.y + 20, 0.f };

	for (int i = 0; i < 4; ++i) {
		m_vOriginOutBox[i] = m_vOutBox[i];
		m_vOriginInBox[i] = m_vInBox[i];
	}

	m_iScaleSize = 1.2f;
	m_fOriginSizeX = 70.f;
	m_fOriginSizeY = 70.f;
}

int CYGBox::Update()
{
	if (m_iScaleSize == 0.f) {

		CObjectManager::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CYGMonster>::Create(700, 300, 50, 50));
		CObjectManager::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CYGGunItem>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y - 40, 50,30));
		CObjectManager::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CYGBulletItem>::Create(m_tInfo.vPos.x + 20, m_tInfo.vPos.y, 30, 30));
		CObjectManager::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CYGBulletItem>::Create(m_tInfo.vPos.x - 20, m_tInfo.vPos.y, 30, 30));
		return OBJ_DEAD;
	}

	m_HitTick++;
	m_tInfo.fSizeX = m_fOriginSizeX * m_iScaleSize;
	m_tInfo.fSizeY = m_fOriginSizeY * m_iScaleSize;
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, m_iScaleSize, m_iScaleSize, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_tInfo.matWorld = matScale * matTrans;

	for (int i = 0; i < 4; ++i) {
		m_vOutBox[i] = m_vOriginOutBox[i];
		m_vOutBox[i] -= {200.f, 300.f, 0.f};
		D3DXVec3TransformCoord(&m_vOutBox[i], &m_vOutBox[i], &m_tInfo.matWorld);

		m_vInBox[i] = m_vOriginInBox[i];
		m_vInBox[i] -= {200.f, 300.f, 0.f};
		D3DXVec3TransformCoord(&m_vInBox[i], &m_vInBox[i], &m_tInfo.matWorld);
	}
	__super::Update_Rect();
	return 0;
}

void CYGBox::Late_Update()
{
	OnCollision();
}

void CYGBox::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollManager::Get_Instance()->Get_ScrollY();


	COLORREF color = RGB(102, 48, 0);

	HBRUSH hBrush = CreateSolidBrush(color);
	HPEN hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	POINT outBox[4];
	for (int i = 0; i < 4; ++i) {
		outBox[i].x = static_cast<LONG>(m_vOutBox[i].x) + iScrollX;
		outBox[i].y = static_cast<LONG>(m_vOutBox[i].y) + iScrollY;
	}
	Polygon(hDC, outBox, 4);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);


	color = RGB(76, 33, 0);
	hBrush = CreateSolidBrush(color);
	hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hOldPen = (HPEN)SelectObject(hDC, hPen);

	POINT inBox[4];
	for (int i = 0; i < 4; ++i) {
		inBox[i].x = static_cast<LONG>(m_vInBox[i].x)+ iScrollX;
		inBox[i].y = static_cast<LONG>(m_vInBox[i].y)+ iScrollY;
	}
	Polygon(hDC, inBox, 4);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	if (g_bDevmode) {
		HitRect(hDC, m_tHitRect, iScrollX, iScrollY);
	}
}

void CYGBox::Release()
{
}

void CYGBox::OnCollision(CObject* _obj)
{
	if (m_HitTick > 20) {
		m_iScaleSize -= 0.3f;
		m_HitTick = 0;
	}
}

void CYGBox::OnCollision()
{
	RECT _copyRect = static_cast<CYGPlayer*>(CObjectManager::Get_Instance()->Get_Player())->Get_CollisionBox();

	float fRadius = (20 + m_tInfo.fSizeX) * 0.5f;

	float x = (_copyRect.right + _copyRect.left) * 0.5f;
	float y = (_copyRect.bottom + _copyRect.top) * 0.5f;

	float fWidth = abs(x - m_tInfo.vPos.x);
	float fHeight = abs(y - m_tInfo.vPos.y);

	float fDiagonal = powf((fWidth * fWidth + fHeight * fHeight), 0.5f);

	bool check =  fRadius >= fDiagonal;

	if (check) {
		if (m_HitTick > 20) {
			m_iScaleSize -= 0.3f;
			m_HitTick = 0;
		}
	}
}
