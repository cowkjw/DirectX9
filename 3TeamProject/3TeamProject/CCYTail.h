#pragma once
#include "CCYObject.h"
class CCYTail : public CCYObject
{
public:
	CCYTail() {}
	virtual ~CCYTail() {}
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;

public:
	void	 Set_TargetHead(CObject* _pHead) { m_targetHead = _pHead; }
	CObject* Get_TargetHead() { return m_targetHead; }

private:
	CObject* m_targetHead;
};

