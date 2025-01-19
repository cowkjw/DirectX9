#include "pch.h"
#include "CYGBulletBox.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CYGBulletItem.h"

CYGBulletBox::CYGBulletBox()
{
}

int CYGBulletBox::Update()
{
	if (m_iScaleSize == 0.f) {
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
