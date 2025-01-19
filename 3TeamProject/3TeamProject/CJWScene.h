#pragma once
#include "CScene.h"
#include "CObjPool.h"
#include "CFruit.h"

struct Fruit_Info
{
	vector<D3DXVECTOR3> vecRenderPoints;
	COLORREF tColor;
	FRUIT_TYPE eFruitType;
};

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

public:
	int Get_Score() const { return m_iScore; }
	int Get_Level() const { return m_iLevel; }
	bool Get_GameOver() const { return m_bGameOver; }
	bool Get_GameClear() const { return m_bGameClear; }
	auto& Get_NextFruit_Info() { return m_tNextFruitInfo; }
	
private:
	void Check_GameOver();
	void BoxLine_Collision();
	void Merge_Fruit();
	void Render_Box(HDC hDC);
	void Find_Proximate_Fruit();
	void Blink_Line();
	void Update_Next_FruitInfo(const vector<D3DXVECTOR3>&,const COLORREF, FRUIT_TYPE);
private:
	unordered_map<FRUIT_TYPE,CObjPool<CFruit>*> m_FruitPoolMap;
	CObject* m_pFruit;
	vector<int> m_vecScore;
	int m_iLevel;
	int m_iScore;
	float m_fDropLenDebug;
	bool m_bGameOver;
	bool m_bGameClear;
	bool m_bCanWarning;
	bool m_bCreated;
	DWORD64 m_dwDroppedTime;
	DWORD64 m_dwDropDelay;
	Fruit_Info m_tNextFruitInfo;
};

