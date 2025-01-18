#pragma once
#include "CScene.h"
#include "CObject.h"

class CCYScene :public CScene
{
public:
	CCYScene();
	virtual ~CCYScene() { Release(); }
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
	enum SLITHERNUM { SL_PLAYER, SL_END };
	vector<vector<CObject>*> m_SlitherSegvec;
	ULONGLONG	m_ullFoodTimeTicker;
};

