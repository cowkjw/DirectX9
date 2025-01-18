#include "pch.h"
#include "CYGBox.h"

CYGBox::CYGBox()
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

}

int CYGBox::Update()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.2f, 1.2f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_tInfo.matWorld = matScale * matTrans;

	for (int i = 0; i < 4; ++i) {
		m_vOutBox[i] = m_vOriginOutBox[i];
		m_vOutBox[i] -= {400.f, 300.f, 0.f};
		D3DXVec3TransformCoord(&m_vOutBox[i], &m_vOutBox[i], &m_tInfo.matWorld);

		m_vInBox[i] = m_vOriginInBox[i];
		m_vInBox[i] -= {400.f, 300.f, 0.f};
		D3DXVec3TransformCoord(&m_vInBox[i], &m_vInBox[i], &m_tInfo.matWorld);
	}


	__super::Update_Rect();
	return 0;
}

void CYGBox::Late_Update()
{
}

void CYGBox::Render(HDC hDC)
{
	COLORREF color = RGB(102, 48, 0);

	HBRUSH hBrush = CreateSolidBrush(color);
	HPEN hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	POINT outBox[4];
	for (int i = 0; i < 4; ++i) {
		outBox[i].x = static_cast<LONG>(m_vOutBox[i].x);
		outBox[i].y = static_cast<LONG>(m_vOutBox[i].y);
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
		inBox[i].x = static_cast<LONG>(m_vInBox[i].x);
		inBox[i].y = static_cast<LONG>(m_vInBox[i].y);
	}
	Polygon(hDC, inBox, 4);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	if (g_bDevmode) {
		HitRect(hDC, m_tHitRect, 0, 0);
	}
}

void CYGBox::Release()
{
}

void CYGBox::OnCollision(CObject* _obj)
{
}
