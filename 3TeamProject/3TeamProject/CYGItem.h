#pragma once
#include "CYGObject.h"
class CYGItem :public CYGObject
{
public:
	CYGItem();
	virtual ~CYGItem() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;
	bool Get_CanPick() { return m_bCanPick; }
	YGITEMTYPE Get_ItemType() { return m_itemType; }
	void Set_Dead() { m_bDead = true; }
private:
	void OnCollision();
protected:
	bool m_bCanPick;
	bool m_bDead;
	YGITEMTYPE m_itemType;
};

