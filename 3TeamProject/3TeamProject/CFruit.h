#pragma once
#include "CObject.h"
enum class FRUIT_TYPE
{
	CHERRY,     
	ORANGE,
	LEMON,
	APPLE,
	PEACH,      
	PINEAPPLE,  
	MELON,      
	PUMPKIN,    
	WATERMELON,
	FT_END
};

enum class FRUIT_STATE
{
	IDLE,
	MERGE, // 합쳐지는 상태
	MERGED, // 합병될 놈
	COOLDOWN,
	FS_END
};
class CFruit : public CObject
{
public:
	CFruit();
	CFruit(FRUIT_TYPE eFruitType, float fMass);
	virtual ~CFruit() { Release(); }

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _obj) override;

public:
	auto Get_FruitType() const { return m_eFruitType; }
	float Get_Radius() const { return m_fRadius; }
	float Get_Mass() const { return m_fMass; }
	auto& Get_Velocity() { return m_vVelocity; }
	auto Get_State() const { return m_eFruitSt; }
	const auto& Get_Scale() const { return m_vScale; }
	auto Get_Color() const { return m_tColor; }
	auto& Get_RenderPoints() const { return m_vecRenderPoints; }
	bool Is_Active() const { return m_bActive; }
	bool Is_Dropped() const { return m_bDropped; }
	bool In_Box() const { return m_bInBox; }

	void Set_Drop(bool bDrop) { m_bDropped = bDrop; }
	void Set_Velocity(const D3DXVECTOR3& vVelo) { m_vVelocity = vVelo; }
	void Set_Type(FRUIT_TYPE eType) { m_eFruitType = eType; }
	void Set_State(FRUIT_STATE eState) { m_eFruitSt = eState; }
	void Set_Active(bool bActive) { m_bActive = bActive; }
	void Set_LinePassed(bool bPassed);

	void Reset(); // 풀링에 쓸 때
	void Set_Merged_Fruit();
private:
	void Drop();
	void Follow_Mpuse();
	void Update_Matrix();
	void Set_Scale();
	void Set_Mass();
	void Set_Radius();
	void Set_Color();
	void Initialize_OriginPoint(int _iCount, float _Radius, float _fStartAngle = 0.f);
private:
	float m_fMass;
	float m_fRadius;
	float m_fAngle;
	float m_fRollingSpeed;
	float m_fMergeAnimRatio;
	const float GRAVITY = 9.8f;
	bool m_bDropped;
	bool m_bIsGround;
	bool m_bActive;
	bool m_bInBox;
	COLORREF m_tColor;
	FRUIT_TYPE m_eFruitType;
	FRUIT_STATE m_eFruitSt;
	D3DXVECTOR3 m_vVelocity;
	D3DXVECTOR3 m_vScale;
	vector<D3DXVECTOR3> m_vecLocalPoints;
	vector<D3DXVECTOR3> m_vecRenderPoints;
	D3DXMATRIX m_matScale;
	D3DXMATRIX m_matRotZ;
	D3DXMATRIX m_matTrans;
	DWORD64 m_dwMergedTime;
	DWORD64 m_dwCanMergeCool;
};

