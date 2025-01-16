#include "pch.h"
#include "CJWScene.h"
#include "CKeyManager.h"

void CJWScene::Initialize()
{
}

int CJWScene::Update()
{
    return 0;
}

void CJWScene::LateUpdate()
{
}

void CJWScene::Render(HDC hDC)
{
}

void CJWScene::Release()
{
}

void CJWScene::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
		g_bDevmode = !g_bDevmode;
	}
}

void CJWScene::Create_MapObj()
{
}

void CJWScene::Offset()
{
}
