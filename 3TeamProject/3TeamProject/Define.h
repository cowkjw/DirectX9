#pragma once

#define WINCX		800
#define WINCY		600

#define	PURE		= 0
#define VK_MAX				0xff

#define OBJ_NOEVENT			0
#define OBJ_DEAD			1	

#define OBJMGR CObjectManager::Get_Instance()
#define GET_PLAYER CObjectManager::Get_Instance()->Get_ObjList_ByID(OBJ_PLAYER).front()



extern HWND		g_hWnd;
extern bool		g_bDevmode;

enum SCENEID { SC_MENU, SC_YG, SC_CY, SC_DW, SC_JW, SC_END };
enum UITYPE{ UI_YG, UI_CY,UI_DW, UI_JW, UI_END};
enum OBJID { OBJ_PLAYER, OBJ_DW_ROAD, OBJ_BULLET, OBJ_MONSTER, OBJ_MISC, OBJ_CYTAIL, OBJ_END};
enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_END };

static D3DXVECTOR3		Get_Mouse()
{
	POINT		pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
}


typedef struct tagInfo
{
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vNormal;	// 법선 벡터(방향 벡터)
	D3DXVECTOR3		vPos;
	D3DXMATRIX		matWorld;
	float fSizeX; //가로 크기
	float fSizeY; //세로 크기
}INFO;

//비트맵 관련
struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& rObj)
	{
		return !lstrcmp(m_pString, rObj.first);
	}

private:
	const TCHAR* m_pString;
};

struct DeleteMap
{
public:
	template<typename T>
	void	operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

//개발 모드
// 충돌 범위
static BOOL HitCircle(HDC hDC, RECT tRect, int x, int y)
{
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);
	Ellipse(hDC, (int)(tRect.left + x), (int)(tRect.top + y), (int)(tRect.right + x), (int)(tRect.bottom + y));
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hNewPen);
	return true;
}

//적 감지용 
static BOOL DetectCircle(HDC hDC, RECT tRect)
{
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);
	Ellipse(hDC, (int)(tRect.left), (int)(tRect.top), (int)(tRect.right), (int)(tRect.bottom));
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hNewPen);
	return true;
}

static BOOL DetectRect(HDC hDC, RECT tRect, int x, int y)
{
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);
	Rectangle(hDC, (int)(tRect.left + x), (int)(tRect.top + y), (int)(tRect.right + x), (int)(tRect.bottom + y));
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hNewPen);
	return true;
}

static BOOL ColorCircleNoPen(HDC hDC, int leftTopX, int leftTopY, int rightBottomX, int rightBottomY, int R, int G, int B) 
{
	COLORREF color = RGB(R, G, B);

	HBRUSH hBrush = CreateSolidBrush(color);
	HPEN hPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	Ellipse(hDC, leftTopX, leftTopY, rightBottomX, rightBottomY);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	return true;
}

static BOOL ColorCircle(HDC hDC, int leftTopX, int leftTopY, int rightBottomX, int rightBottomY, int R, int G, int B, int penSize)
{
	COLORREF color = RGB(R, G, B);

	HBRUSH hBrush = CreateSolidBrush(color);
	HPEN hPen = CreatePen(PS_SOLID, penSize, RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	Ellipse(hDC, leftTopX, leftTopY, rightBottomX, rightBottomY);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	return true;
}