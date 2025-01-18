#pragma once
#include "CCYObject.h"
class CCYPlayer :  public CCYObject
{
public:
	CCYPlayer();
	virtual ~CCYPlayer();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;

public:
	float Get_WormSize() { return m_fWormSize; }
	int	 Get_WormLength() { if (m_TailSeglist.empty()) return 0; else return m_TailSeglist.size(); }

private:
	void Key_Input();
	void Increase_TailSegment();
private:
	D3DXMATRIX	matScale;
	D3DXMATRIX	matRotZ;
	D3DXMATRIX	matTrans;
	float       m_fAngle;
	D3DXVECTOR3 m_vEyePoint[4];

	list<CObject*> m_TailSeglist;

	float		m_fWormSize;
	ULONGLONG	m_ullTailDeleteTicker;
	bool		m_bDashing;

};

