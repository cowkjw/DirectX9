#include "pch.h"
#include "CMenuScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"

CMenuScene::CMenuScene():m_iIndex(0)
{
}

void CMenuScene::Initialize()
{
}

int CMenuScene::Update()
{
    Key_Input();
    return 0;
}

void CMenuScene::Late_Update()
{
}

void CMenuScene::Render(HDC hDC)
{
    COLORREF color = RGB(0, 0, 0);
    HBRUSH hBrush = CreateSolidBrush(color);
    HPEN hPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
    Rectangle(hDC, -100, -100, 900, 700);
    SelectObject(hDC, hOldBrush);
    SelectObject(hDC, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPen);

    color = RGB(255, 255, 255);
    hBrush = CreateSolidBrush(color);
    hPen = CreatePen(PS_SOLID, 3, RGB(128, 128, 128));
    hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    hOldPen = (HPEN)SelectObject(hDC, hPen);

    for (int i = 0; i < 4; ++i) {
        if (i != m_iIndex) {
            Rectangle(hDC, 20 + (200*i), 200, 180 + (200 * i), 400);
        }
    }

    SelectObject(hDC, hOldBrush);
    SelectObject(hDC, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPen);

    color = RGB(255, 255, 255);
    hBrush = CreateSolidBrush(color);
    hPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
    hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    hOldPen = (HPEN)SelectObject(hDC, hPen);

    Rectangle(hDC, 10 + (200 * m_iIndex), 190, 190 + (200 * m_iIndex), 410);

    SelectObject(hDC, hOldBrush);
    SelectObject(hDC, hOldPen);
    DeleteObject(hBrush);
    DeleteObject(hPen);


    SetTextColor(hDC, RGB(255, 255, 255)); //글자 색
    SetBkMode(hDC, TRANSPARENT); //글자 배경 투명

    TCHAR whoMake[64];
    _stprintf_s(whoMake, _T("유경"));
    RECT rect = { 20, 410, 180, 450 };
    DrawText(hDC, whoMake, _tcslen(whoMake), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    _stprintf_s(whoMake, _T("채영"));
    rect = { 220, 410, 380, 450 };
    DrawText(hDC, whoMake, _tcslen(whoMake), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    _stprintf_s(whoMake, _T("동완"));
    rect = { 420, 410, 580, 450 };
    DrawText(hDC, whoMake, _tcslen(whoMake), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    _stprintf_s(whoMake, _T("장원"));
    rect = { 620, 410, 780, 450 };
    DrawText(hDC, whoMake, _tcslen(whoMake), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

void CMenuScene::Release()
{
}

void CMenuScene::Key_Input()
{
    if (CKeyManager::Get_Instance()->Key_Down(VK_RIGHT)) {
        m_iIndex++;
        if (m_iIndex > 3) {
            m_iIndex = 0;
        }
    }

    if (CKeyManager::Get_Instance()->Key_Down(VK_LEFT)) {
        m_iIndex--;
        if (m_iIndex < 0) {
            m_iIndex = 3;
        }
    }

    if (CKeyManager::Get_Instance()->Key_Down(VK_SPACE)) {
        switch (m_iIndex)
        {
        case 0:
            CSceneManager::Get_Instance()->Set_Scene(SC_YG);
            break;
        case 1:
            CSceneManager::Get_Instance()->Set_Scene(SC_CY);
            break;
        case 2:
            CSceneManager::Get_Instance()->Set_Scene(SC_DW);
            break;
        case 3:
            CSceneManager::Get_Instance()->Set_Scene(SC_JW);
            break;
        default:
            break;
        }
    }
}

void CMenuScene::Create_MapObj()
{
}

void CMenuScene::Offset()
{
}