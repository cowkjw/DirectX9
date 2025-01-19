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

bool CCollisionManager::Check_Circle(RECT _Dst, RECT _Src)
{
    float _DstSize = _Dst.right - _Dst.left;
    float _SrcSize = _Src.right - _Src.left;
    float fRadius = (_DstSize + _SrcSize) * 0.5f;

    float _DstX = (_Dst.right + _Dst.left) * 0.5f;
    float _DstY = (_Dst.top + _Dst.bottom) * 0.5f;
    float _SrcX = (_Src.right + _Src.left) * 0.5f;
    float _SrcY = (_Src.top + _Src.bottom) * 0.5f;

    float fWidth = abs(_DstX- _SrcX);
    float fHeight = abs(_DstY - _SrcY);

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
    if (!_Dst || !_Src)
        return false;

    // 멀리 있는 장애물 무시
    if (_Src->vPos.z > 600.f)
        return false;

    auto pPlayer = dynamic_cast<CDWPlayer*>(_Dst);
    auto* pObsScr = _Src->screenCorner;    // 장애물 스크린 좌표


    const float paddingX = 10.f;  // 충돌 x축 반경임
    const float paddingY = 1.f;   // 충돌 y축 반경임

    float minX = min(min(pObsScr[0].x, pObsScr[1].x), min(pObsScr[2].x, pObsScr[3].x)) - paddingX;
    float maxX = max(max(pObsScr[0].x, pObsScr[1].x), max(pObsScr[2].x, pObsScr[3].x)) + paddingX;
    float minY = min(min(pObsScr[0].y, pObsScr[1].y), min(pObsScr[2].y, pObsScr[3].y)) - paddingY;
    float maxY = max(max(pObsScr[0].y, pObsScr[1].y), max(pObsScr[2].y, pObsScr[3].y)) + paddingY;

    float PlayerX = pPlayer->Get_RenderPoint()->x;
    float PlayerY = pPlayer->Get_RenderPoint()->y;

    // 충돌 확인
    if (PlayerX >= minX && PlayerX <= maxX &&
        PlayerY >= minY && PlayerY <= maxY)
    {
        return true;
    }

    return false;
}
