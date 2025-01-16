#include "pch.h"
#include "CCYScene.h"
#include "CKeyManager.h"

void CCYScene::Initialize()
{
}

int CCYScene::Update()
{
    return 0;
}

void CCYScene::LateUpdate()
{
}

void CCYScene::Render(HDC hDC)
{
}

void CCYScene::Release()
{
}

void CCYScene::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
		g_bDevmode = !g_bDevmode;
	}
}

void CCYScene::Create_MapObj()
{
}

void CCYScene::Offset()
{
}
