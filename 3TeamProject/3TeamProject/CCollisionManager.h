#pragma once
#include "CObject.h"
#include "CFruit.h"

class CCollisionManager
{
public:
	static void Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src);
	static bool Check_Circle(CObject* _Dst, CObject* _Src);

	static void JW_Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src);
	static bool JW_Check_Circle(CObject* _Dst, CObject* _Src);
};

