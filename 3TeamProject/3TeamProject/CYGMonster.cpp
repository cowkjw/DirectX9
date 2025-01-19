#include "pch.h"
#include "CYGMonster.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CYGBullet.h"

CYGMonster::CYGMonster():m_iShootTick(0)
{
}

void CYGMonster::Initialize()
{
	m_eOBJID = OBJ_MONSTER;
	m_eRender = RENDER_GAMEOBJECT;

	m_vLeftGunHandPos = { 695.f, 240.f, 0.f };
	m_vRightGunHandPos = { 705.f, 270.f, 0.f };
	m_vOriginLeftGunHand = m_vLeftGunHandPos;
	m_vOriginRightGunHand = m_vRightGunHandPos;

	m_vGunRectanglePoint[0] = { 695.f, 210.f, 0.f };
	m_vGunRectanglePoint[1] = { 705.f, 210.f, 0.f };
	m_vGunRectanglePoint[2] = { 705.f, 280.f, 0.f };
	m_vGunRectanglePoint[3] = { 695.f, 280.f, 0.f };

	m_vBulletSpawn = { 700.f, 210.f, 0.f };
	m_vOriginBulletSpawn = m_vBulletSpawn;

	for (int i = 0; i < 4; ++i) {
		m_vOriginGunRectanglePoint[i] = m_vGunRectanglePoint[i];
	}

	m_vOriginPos = m_tInfo.vPos;

	m_targetObj = CObjectManager::Get_Instance()->Get_Player();

	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_fSpeed = 2.f;

	m_iHp = 50;
	m_iMaxHp = m_iHp;
}

int CYGMonster::Update()
{
	if (m_iHp <= 0) {
		return OBJ_DEAD;
	}
	m_iShootTick++;
	if (m_iShootTick > 20) {
		CObjectManager::Get_Instance()->Add_Object(OBJ_MONSTERBULLET, CAbstractFactory<CYGBullet>::Create(m_vBulletSpawn.x, m_vBulletSpawn.y));
		static_cast<CYGBullet*>(CObjectManager::Get_Instance()->Get_ObjList_ByID(OBJ_MONSTERBULLET).back())->Set_Dir(m_tInfo.vLook);
		m_iShootTick = 0;
	}
	m_tInfo.vLook = m_targetObj->Get_Info().vPos - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);
	m_fAngle = D3DXToDegree(atan2f(m_tInfo.vLook.y, m_tInfo.vLook.x));

	if (m_fAngle < 0) {
		m_fAngle += 360;
	}
	m_fAngle += 100;

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle / 60);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;


	m_vLeftGunHandPos = m_vOriginLeftGunHand;
	m_vLeftGunHandPos -= {700.f, 300.f, 0.f};
	D3DXVec3TransformCoord(&m_vLeftGunHandPos, &m_vLeftGunHandPos, &m_tInfo.matWorld);

	m_vRightGunHandPos = m_vOriginRightGunHand;
	m_vRightGunHandPos -= {700.f, 300.f, 0.f};
	D3DXVec3TransformCoord(&m_vRightGunHandPos, &m_vRightGunHandPos, &m_tInfo.matWorld);

	for (int i = 0; i < 4; ++i) {
		m_vGunRectanglePoint[i] = m_vOriginGunRectanglePoint[i];
		m_vGunRectanglePoint[i] -= {700.f, 300.f, 0.f};
		D3DXVec3TransformCoord(&m_vGunRectanglePoint[i], &m_vGunRectanglePoint[i], &m_tInfo.matWorld);
	}

	m_vBulletSpawn = m_vOriginBulletSpawn;
	m_vBulletSpawn -= {700.f, 300.f, 0.f};
	D3DXVec3TransformCoord(&m_vBulletSpawn, &m_vBulletSpawn, &m_tInfo.matWorld);

	if (m_tInfo.vPos.y == 50) {
		m_tInfo.vDir = { 0.f, 1.f, 0.f };
	}

	if (m_tInfo.vPos.y == 550) {
		m_tInfo.vDir = { 0.f, -1.f, 0.f };
	}

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;


	__super::Update_Rect();
	return 0;
}

void CYGMonster::Late_Update()
{
}

void CYGMonster::Render(HDC hDC)
{
	POINT point[4];
	point[0] = { (long)m_vGunRectanglePoint[0].x, (long)m_vGunRectanglePoint[0].y };
	point[1] = { (long)m_vGunRectanglePoint[1].x, (long)m_vGunRectanglePoint[1].y };
	point[2] = { (long)m_vGunRectanglePoint[2].x, (long)m_vGunRectanglePoint[2].y };
	point[3] = { (long)m_vGunRectanglePoint[3].x, (long)m_vGunRectanglePoint[3].y };
	ColorPolygon(hDC, point, 4, 111, 70, 49, 1);

	ColorCircle(hDC, m_vLeftGunHandPos.x - 10 , m_vLeftGunHandPos.y - 10 , m_vLeftGunHandPos.x + 10 , m_vLeftGunHandPos.y + 10 , 252, 194, 114, 2); // ¿Þ¼Õ
	ColorCircle(hDC, m_vRightGunHandPos.x - 10 , m_vRightGunHandPos.y - 10 , m_vRightGunHandPos.x + 10 , m_vRightGunHandPos.y + 10 , 252, 194, 114, 2); // ¿À¸¥¼Õ

	ColorCircle(hDC, m_tHitRect.left, m_tHitRect.top , m_tHitRect.right, m_tHitRect.bottom, 252, 194, 114, 2);

	COLORREF color = RGB(255, 255, 255);
	HBRUSH hBrush = CreateSolidBrush(color);
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, m_tInfo.vPos.x - 50, m_tInfo.vPos.y-50, m_tInfo.vPos.x + 50, m_tInfo.vPos.y - 40, 10, 10);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	int hpWidth = 100 * m_iHp / m_iMaxHp;

	color = RGB(179, 179, 179);
	hBrush = CreateSolidBrush(color);
	hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hOldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, m_tInfo.vPos.x - 50, m_tInfo.vPos.y - 50, m_tInfo.vPos.x - 50 + hpWidth, m_tInfo.vPos.y - 40, 10, 10);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void CYGMonster::Release()
{
}

void CYGMonster::OnCollision(CObject* _obj)
{
}
