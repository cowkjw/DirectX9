#include "pch.h"
#include "CYGScene.h"
#include "CKeyManager.h"

CYGScene::CYGScene()
{
}

void CYGScene::Initialize()
{
}

int CYGScene::Update()
{
    return 0;
}

void CYGScene::LateUpdate()
{
}

void CYGScene::Render(HDC hDC)
{
}

void CYGScene::Release()
{
}

void CYGScene::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
		g_bDevmode = !g_bDevmode;
	}
}

void CYGScene::Create_MapObj()
{
}

void CYGScene::Offset()
{
}
