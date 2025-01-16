#pragma once
#include "CScene.h"
#include "CObjPool.h"
#include "CFruit.h"
class CJWScene :public CScene
{
public:
	CJWScene();
	virtual ~CJWScene() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Key_Input() override;
	void Create_MapObj() override;
	void Offset() override;
private:
	unordered_map<FRUIT_TYPE, CObjPool<CFruit>*> m_FruitPoolMap;
	vector<CObject*> m_vecFruit;
	CObject* m_pFruit;
	list<CObject*> m_FruitList;
	int m_iLevel;
	bool m_bCreated;
	DWORD64 m_dwDroppedTime;
	DWORD64 m_dwDropDelay;
};

