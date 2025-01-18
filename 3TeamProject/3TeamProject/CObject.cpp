#include "pch.h"
#include "CObject.h"

CObject::CObject():m_fSpeed(0)
{

	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CObject::~CObject(){

}

void CObject::Update_Rect()
{
	// �̰� m_tInfo.fSizeX�� Y 50���� �ʱ�ȭ ���ִ� �κ��� �־��??
	//�Ⱥ��̴µ� ��� 50���� ������� �̾���,,,
	m_tHitRect.left = m_tInfo.vPos.x - m_tInfo.fSizeX * 0.5f;
	m_tHitRect.top = m_tInfo.vPos.y - m_tInfo.fSizeY * 0.5f;
	m_tHitRect.right = m_tInfo.vPos.x + m_tInfo.fSizeX * 0.5f;
	m_tHitRect.bottom = m_tInfo.vPos.y + m_tInfo.fSizeY * 0.5f;
}
