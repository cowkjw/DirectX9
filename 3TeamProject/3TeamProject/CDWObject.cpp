#include "pch.h"
#include "CDWObject.h"

CDWObject::CDWObject()
    :m_pRenderPoint(nullptr)
{
    ZeroMemory(&m_tInfo, sizeof(m_tInfo));
    D3DXMatrixIdentity(&m_tInfo.matWorld);
}

CDWObject::~CDWObject()
{
    // 동적 메모리 해제
    if (m_pRenderPoint)
    {
        delete[] m_pRenderPoint;
        m_pRenderPoint = nullptr;
    }
}

void CDWObject::Initialize_OriginPoint(const int& _iCount, const int& _Radius, const float& _fStartAngle)
{
    m_vOriginPointvec.clear();
    m_vPointvec.clear();
    m_vOriginPointvec.reserve(_iCount);
    m_vPointvec.reserve(_iCount);
    m_fRadius = _Radius;

    


    m_pRenderPoint = new POINT[_iCount];

    float fUnitAngle = 360.f / (float)_iCount;
    float CurAngle(0.f);

    for (int i = 0; i < _iCount; ++i)
    {
        CurAngle = D3DXToRadian(_fStartAngle + fUnitAngle * i);
        m_vOriginPointvec.push_back({ _Radius * cosf(CurAngle), _Radius * sinf(CurAngle) , 0.f });
        m_vPointvec.push_back({ _Radius * cosf(CurAngle), _Radius * sinf(CurAngle) , 0.f });
        m_pRenderPoint[i] = { long(_Radius * cosf(CurAngle)), long(_Radius * sinf(CurAngle)) };
    }
}
