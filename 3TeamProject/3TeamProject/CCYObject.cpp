#include "pch.h"
#include "CCYObject.h"

CCYObject::~CCYObject()
{
    if (m_pRenderPoint != nullptr)
        delete[] m_pRenderPoint;
}

void CCYObject::Initialize_OriginPoint(const int& _iCount, const int& _Radius, const float& _fStartAngle)
{
    m_vOriginPointvec.reserve(_iCount);
    m_vPointvec.reserve(_iCount);
    m_fRadius = _Radius;

    float fUnitAngle = 360.f / (float)_iCount;
    float CurAngle(0.f);
    m_pRenderPoint = new POINT[_iCount];

    for (int i = 0; i < _iCount; ++i)
    {
        CurAngle = D3DXToRadian(_fStartAngle + fUnitAngle * i);
        m_vOriginPointvec.push_back({ _Radius * cosf(CurAngle), _Radius * sinf(CurAngle) , 0.f });
        m_vPointvec.push_back({ _Radius * cosf(CurAngle), _Radius * sinf(CurAngle) , 0.f });
        m_pRenderPoint[i] = { long(_Radius * cosf(CurAngle)), long(_Radius * sinf(CurAngle)) };
    }
}

COLORREF CCYObject::SetRGB(BYTE r, BYTE g, BYTE b)
{
    return RGB(r, g, b); 
}

// 각 색상의 값 분리 함수 
void CCYObject::GetRGB(COLORREF color, BYTE* r, BYTE* g, BYTE* b)
{
    *r = GetRValue(color);
    *g = GetGValue(color);
    *b = GetBValue(color); 
} 

// RGB 값을 조정하는 함수
COLORREF CCYObject::AdjustRGB(COLORREF& color, int adjust)
{
    BYTE r, g, b; GetRGB(color, &r, &g, &b); 
// 값 조정
    r = (BYTE)max(0, min(255, r - adjust));
    g = (BYTE)max(0, min(255, g - adjust));
    b = (BYTE)max(0, min(255, b - adjust));
    color = SetRGB(r, g, b);
    return color;
}