#pragma once
#include "CCYHead.h"
class CCYPlayer :  public CCYHead
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

private:
	void Key_Input();
	void Increase_TailSegment();

private:
	float		m_fWormSize;
	ULONGLONG	m_ullTailDeleteTicker;
	bool		m_bDashing;
	int			m_iDeadTimeFrame;
};

