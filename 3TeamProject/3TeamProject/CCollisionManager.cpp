#include "pch.h"
#include "CCollisionManager.h"

void CCollisionManager::Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src)
{
    RECT rc{};

    for (auto& Dst : _Dst)
    {
        for (auto& Src : _Src)
        {
            if (Check_Circle(Dst, Src))
            {
                Dst->OnCollision(Src);
                Src->OnCollision(Dst);
            }
        }
    }
}

bool CCollisionManager::Check_Circle(CObject* _Dst, CObject* _Src)
{
    float fRadius = (_Dst->Get_Info().fSizeX + _Src->Get_Info().fSizeX) * 0.5f;

    float fWidth = abs(_Dst->Get_Info().vPos.x - _Src->Get_Info().vPos.x);
    float fHeight = abs(_Dst->Get_Info().vPos.y - _Src->Get_Info().vPos.y);

    float fDiagonal = powf((fWidth * fWidth + fHeight * fHeight), 0.5f);

    return fRadius >= fDiagonal;
}
