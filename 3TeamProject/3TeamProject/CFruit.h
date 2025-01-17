#pragma once
#include "CObject.h"
enum class FRUIT_TYPE
{
	ORANGE,
	LEMON,
	APPLE,
	WATERMELON,
	END
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
	bool Is_Dropped() const { return m_bDropped; }
	void Set_Velocity(const D3DXVECTOR3& vVelo) { m_vVelocity = vVelo; }
	void Set_Type(FRUIT_TYPE eType) { m_eFruitType = eType; }
	void Reset();

private:
	void Drop();
	void Follow_Mpuse();
	void Update_Matrix();
	void Set_Mass();
	void Set_Radius();
	void Set_Color();
	void Initialize_OriginPoint(int _iCount, float _Radius, float _fStartAngle = 0.f);
private:
	float m_fMass;
	float m_fRadius;
	float m_fAngle;
	float m_fRollingSpeed;
	const float GRAVITY = 9.8f;
	bool m_bDropped;
	bool m_bIsGround;
	COLORREF m_tColor;
	FRUIT_TYPE m_eFruitType;
	D3DXVECTOR3 m_vVelocity;
	D3DXVECTOR3 m_vScale;
	vector<D3DXVECTOR3> m_vecLocalPoints;
	vector<D3DXVECTOR3> m_vecRenderPoints;
	D3DXMATRIX m_matScale;
	D3DXMATRIX m_matRotZ;
	D3DXMATRIX m_matTrans;
};

