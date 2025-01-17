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
	// 이거 m_tInfo.fSizeX랑 Y 50으로 초기화 해주는 부분이 있어요??
	//안보이는데 계속 50으로 ㄷ르어가서 쫄았음,,,
	m_tHitRect.left = m_tInfo.vPos.x - m_tInfo.fSizeX * 0.5f;
	m_tHitRect.top = m_tInfo.vPos.y - m_tInfo.fSizeY * 0.5f;
	m_tHitRect.right = m_tInfo.vPos.x + m_tInfo.fSizeX * 0.5f;
	m_tHitRect.bottom = m_tInfo.vPos.y + m_tInfo.fSizeY * 0.5f;
}
