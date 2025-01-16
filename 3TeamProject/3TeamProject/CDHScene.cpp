#include "pch.h"
#include "CDHScene.h"
#include "CKeyManager.h"

void CDHScene::Initialize()
{
}

int CDHScene::Update()
{
    return 0;
}

void CDHScene::LateUpdate()
{
}

void CDHScene::Render(HDC hDC)
{
}

void CDHScene::Release()
{
}

void CDHScene::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Down(VK_F1)) {
		g_bDevmode = !g_bDevmode;
	}
}

void CDHScene::Create_MapObj()
{
}

void CDHScene::Offset()
{
}
