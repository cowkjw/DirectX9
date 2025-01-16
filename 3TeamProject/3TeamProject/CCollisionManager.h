#pragma once
#include "CObject.h"

class CCollisionManager
{
public:
	static void Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src);
	static bool Check_Circle(CObject* _Dst, CObject* _Src);
};

