#include "pch.h"
#include "CCollisionManager.h"
#include "CDWPlayer.h"

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


void CCollisionManager::JW_Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src)
{
    for (auto& Dst : _Dst)
    {
        for (auto& Src : _Src)
        {
            if (Dst == Src)
            {
                continue;
            }

            if (JW_Check_Circle(Dst, Src))
            {
                Dst->OnCollision(Src);
                // Src->OnCollision(Dst);
            }
        }
    }
}
bool CCollisionManager::JW_Check_Circle(CObject* _Dst, CObject* _Src)
{
    CFruit* pFruit1 = dynamic_cast<CFruit*>(_Dst);
    CFruit* pFruit2 = dynamic_cast<CFruit*>(_Src);

    if (!pFruit1 || !pFruit2) return false;

    float fObj1RadiMultiScale = pFruit1->Get_Radius()* pFruit1->Get_Scale().x;
    float fObj2RadiMultiScale = pFruit2->Get_Radius() * pFruit2->Get_Scale().x;

    float fDist = hypotf(pFruit2->Get_Info().vPos.x - pFruit1->Get_Info().vPos.x
        , pFruit2->Get_Info().vPos.y - pFruit1->Get_Info().vPos.y);
    return fDist <= fObj1RadiMultiScale + fObj2RadiMultiScale;
}

bool CCollisionManager::DW_Check_Coll(CObject* _Dst, CRoad::SObstacle* _Src)
{

   if (!_Dst) return false;

   if (!_Src) return false;
    CRoad::SObstacle* pObs = dynamic_cast<CRoad::SObstacle*>(_Src);

    for (int i = 0; i < 4; i++)
    {
        pObs->worldCorner[i];
    }
    
         

    return false;
}

