#include "pch.h"
#include "CMenuScene.h"
#include "CKeyManager.h"
#include "CSceneManager.h"

CMenuScene::CMenuScene()
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
    Rectangle(hDC, -100, -100, 900, 700);
}

void CMenuScene::Release()
{
}

void CMenuScene::Key_Input()
{
    if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
        CSceneManager::Get_Instance()->Set_Scene(SC_YG);
    }

    if (CKeyManager::Get_Instance()->Key_Down(VK_F2)) {
        CSceneManager::Get_Instance()->Set_Scene(SC_CY);
    }

    if (CKeyManager::Get_Instance()->Key_Down(VK_F3)) {
        CSceneManager::Get_Instance()->Set_Scene(SC_DW);
    }

    if (CKeyManager::Get_Instance()->Key_Down(VK_F4)) {
        CSceneManager::Get_Instance()->Set_Scene(SC_JW);
    }
}

void CMenuScene::Create_MapObj()
{
}

void CMenuScene::Offset()
{
}
