#pragma once

#define WINCX		800
#define WINCY		600

#define	PURE		= 0
#define VK_MAX				0xff

#define OBJ_NOEVENT			0
#define OBJ_DEAD			1	

extern HWND		g_hWnd;
extern bool		g_bDevmode;

enum SCENEID { SC_MENU, SC_YG, SC_CY, SC_DH, SC_JW, SC_END };
enum UITYPE{UI_YG, UI_CY,UI_DH, UI_JW, UI_END};
enum OBJID {OBJ_PLAYER, OBJ_END};
enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_END };


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


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}