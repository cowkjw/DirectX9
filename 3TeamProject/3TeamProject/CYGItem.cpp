#include "pch.h"
#include "CYGItem.h"

CYGItem::CYGItem()
{
}

void CYGItem::Initialize()
{
    m_eOBJID = OBJ_ITEM;
    m_eRender = RENDER_GAMEOBJECT;
}

int CYGItem::Update()
{
    return 0;
}

void CYGItem::Late_Update()
{
}

void CYGItem::Render(HDC hDC)
{
}

void CYGItem::Release()
{
}

void CYGItem::OnCollision(CObject* _obj)
{
}

void CYGItem::OnCollision()
{
}
