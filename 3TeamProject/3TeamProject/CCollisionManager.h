#pragma once
#include "CObject.h"
#include "CFruit.h"
#include "CRoad.h"


class CCollisionManager
{
public:
	static void Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src);
	static bool Check_Circle(CObject* _Dst, CObject* _Src);
	static bool Check_Circle(RECT _Dst, RECT _Src);
	static void JW_Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src);
	static bool JW_Check_Circle(CObject* _Dst, CObject* _Src);
	static bool DW_Check_Coll(CObject* _Dst,CRoad::SObstacle* _Src);
};

