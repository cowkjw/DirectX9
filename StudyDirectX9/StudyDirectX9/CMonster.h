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
};

