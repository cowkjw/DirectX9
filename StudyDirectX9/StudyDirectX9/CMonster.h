#pragma once
#include "CObject.h"
class CMonster : public CObject
{
public:
    CMonster();
    virtual ~CMonster() { Release(); }
public:
    void Initialize() override;
    void Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
    void	Set_Player(CObject* pPlayer) { m_pPlayer = pPlayer; }
private:
    CObject* m_pPlayer;
    D3DXVECTOR3 m_tPosin;
    float m_fAngle;
};

