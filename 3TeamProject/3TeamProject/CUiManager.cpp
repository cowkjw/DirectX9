#include "pch.h"
#include "CUiManager.h"
#include "CObjectManager.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CYGPlayer.h"
#include "CJWScene.h"

CUiManager* CUiManager::m_pInstance = nullptr;

CUiManager::CUiManager():m_eCurUi(UI_END)
{
}

CUiManager::~CUiManager()
{
}

void CUiManager::Render(HDC hDC)
{
	switch (m_eCurUi)
	{
	case UI_YG:
		RenderUi_YG(hDC);
		break;
	case UI_CY:
		RenderUi_CY(hDC);
		break;
	case UI_DW:
		RenderUi_DW(hDC);
		break;
	case UI_JW:
		RenderUi_JW(hDC);
		break;
	case UI_END:
		break;
	default:
		break;
	}
}

void CUiManager::RenderUi_YG(HDC hDC)
{
	CYGPlayer* _copyYGPlayer = static_cast<CYGPlayer*>(CObjectManager::Get_Instance()->Get_Player());
	int hpWidth = (400 * _copyYGPlayer->Get_Hp()) / _copyYGPlayer->Get_MaxHp();

	COLORREF color = RGB(179, 179, 179);
	HBRUSH hBrush = CreateSolidBrush(color);
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	RoundRect(hDC, WINCX/2-200,510, WINCX / 2 - 200 + hpWidth, 550, 10, 10);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	switch (_copyYGPlayer->Get_PS()) {
	case CYGPlayer::PS_NOGUN:
		color = RGB(0, 200, 230);
		hBrush = CreateSolidBrush(color);
		hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hOldPen = (HPEN)SelectObject(hDC, hPen);
		RoundRect(hDC, 690, 490, 790, 560, 10, 10);

		SelectObject(hDC, hOldBrush);
		SelectObject(hDC, hOldPen);
		DeleteObject(hBrush);
		DeleteObject(hPen);
		ColorCircle(hDC, 730- 15, 515, 750-15, 535,252,194,114,2);
		ColorCircle(hDC, 730+15, 515, 750+15, 535,252,194,114,2);

		break;
	case CYGPlayer::PS_GUN:
		color = RGB(0, 200, 230);
		hBrush = CreateSolidBrush(color);
		hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hOldPen = (HPEN)SelectObject(hDC, hPen);
		RoundRect(hDC, 690, 490, 790, 560, 10, 10);

		SelectObject(hDC, hOldBrush);
		SelectObject(hDC, hOldPen);
		DeleteObject(hBrush);
		DeleteObject(hPen);

		ColorRect(hDC, 740 - 25 , 525 - 15 , 740 + 25 ,525, 0,0,0,0);
		ColorRect(hDC, 740 +10 , 525, 740 + 25, 525 +15, 0,0,0,0);
		MoveToEx(hDC, 740, 525, nullptr);
		LineTo(hDC, 740 +3, 525+7);
		LineTo(hDC, 740+10, 525+7);

		SetTextColor(hDC, RGB(255, 255, 255)); //글자 색
		SetBkMode(hDC, TRANSPARENT); //글자 배경 투명

		TCHAR bulletNum[64];
		_stprintf_s(bulletNum, _T("%d"), _copyYGPlayer->Get_BulletNum());
		RECT rect2 = { 740, 540, 780, 550 };
		DrawText(hDC, bulletNum, _tcslen(bulletNum), &rect2, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);

		break;
	}

}

void CUiManager::RenderUi_CY(HDC hDC)
{
}

void CUiManager::RenderUi_DW(HDC hDC)
{
}

void CUiManager::RenderUi_JW(HDC hDC)
{
	// 색깔 크기 반지름
	CJWScene* pScene = dynamic_cast<CJWScene*>(CSceneManager::Get_Instance()->Get_Scene());
	if (pScene)
	{
		auto& info =  pScene->Get_NextFruit_Info();

		if (info.vecRenderPoints.empty()) return;
		HBRUSH hBrush = CreateSolidBrush(pScene->Get_NextFruit_Info().tColor);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		vector<D3DXVECTOR3> m_vecRenderPoints = info.vecRenderPoints;
		vector<POINT> m_vecPolyPoints;
		D3DXVECTOR3 vScale(1.f, 1.f, 1.f);

		D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
		switch (info.eFruitType)
		{
		case FRUIT_TYPE::CHERRY:     // 3 * 2.0 = 6 단위
			vScale = {3.5f,3.5f,3.5f };  // 기준점
			break;
		case FRUIT_TYPE::ORANGE:     // 10 * 1.8 = 18 단위
			vScale = { 1.5f, 1.5f, 1.5f };
			break;
		case FRUIT_TYPE::LEMON:      // 15 * 1.6 = 24 단위
			vScale = { 1.5f, 1.5f, 1.5f };
			break;
		case FRUIT_TYPE::APPLE:      // 30 * 1.4 = 42 단위
			vScale = { 1.2f, 1.2f, 1.2f };
			break;
		case FRUIT_TYPE::PEACH:      // 35 * 1.2 = 42 단위
			vScale = { 1.2f, 1.2f, 1.2f };
			break;
		case FRUIT_TYPE::PINEAPPLE:  // 40 * 1.0 = 40 단위
			vScale = { 1.0f, 1.0f, 1.0f };
			break;
		case FRUIT_TYPE::MELON:      // 50 * 0.8 = 40 단위
			vScale = { 0.8f,0.8f,0.8f };
			break;
		case FRUIT_TYPE::PUMPKIN:    // 60 * 0.6 = 36 단위
			vScale = { 0.6f, 0.6f, 0.6f };
			break;
		case FRUIT_TYPE::WATERMELON: // 70 * 0.4 = 28 단위
			vScale = { 0.4f, 0.4f, 0.4f };
			break;
		default:
			vScale = { 1.0f, 1.0f, 1.0f };
			break;
		}
		
		D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
		D3DXMatrixRotationZ(&matRotZ, 0.f);
		D3DXMatrixTranslation(&matTrans, 730.f, 50.f, 0.f);

		for (int i = 0; i < (int)m_vecRenderPoints.size(); i++)
		{
			matWorld = matScale * matRotZ* matTrans;

			// 해당 점 변환
			D3DXVec3TransformCoord(&m_vecRenderPoints[i], &m_vecRenderPoints[i], &matWorld);
		}

		// 폴리곤 
		for (const auto& p : m_vecRenderPoints)
		{
			m_vecPolyPoints.push_back({ (LONG)p.x,(LONG)p.y});
		}
	
		Polygon(hDC, m_vecPolyPoints.data(), (int)m_vecPolyPoints.size());

		D3DXVECTOR3 vDir = (m_vecRenderPoints.front() - D3DXVECTOR3(730.f, 50.f, 0.f));
		float fRadius =D3DXVec3Length(&vDir);
		Ellipse(hDC,
			int(m_vecRenderPoints[50].x - fRadius / 3.f),
			int(m_vecRenderPoints[50].y - fRadius / 3.f),
			int(m_vecRenderPoints[50].x + fRadius / 3.f),
			int(m_vecRenderPoints[50].y + fRadius / 3.f));

		SelectObject(hDC,hOldBrush);
		DeleteObject(hBrush);
	}
	int baseX = 50;
	int baseY = 50;
	int size = 30;    // 숫자 크기
	int depth = 10;   // 입체감을 위한 깊이
	int gap = 50;     // 숫자 간격
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	//// 숫자 0
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // 앞면 상단
	//LineTo(hDC, baseX + size, baseY + size);       // 앞면 우측
	//LineTo(hDC, baseX, baseY + size);              // 앞면 하단
	//LineTo(hDC, baseX, baseY);                     // 앞면 좌측
	//// 윗면
	//LineTo(hDC, baseX + depth, baseY - depth);     // 좌측 상단 사선
	//LineTo(hDC, baseX + size + depth, baseY - depth); // 윗면 상단
	//LineTo(hDC, baseX + size, baseY);              // 우측 상단 사선
	//// 우측면
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth); // 우측 사선
	//LineTo(hDC, baseX + size, baseY + size);       // 우측 하단 연결

	//// 숫자 1
	baseX += gap;
	int midX = baseX + size / 2;
	MoveToEx(hDC, midX, baseY, NULL);
	LineTo(hDC, midX, baseY + size);               // 앞면 수직선
	// 윗면
	MoveToEx(hDC, midX, baseY, NULL);
	LineTo(hDC, midX + depth, baseY - depth);      // 상단 사선
	// 우측면
	LineTo(hDC, midX + depth, baseY + size - depth);
	LineTo(hDC, midX, baseY + size);               // 하단 연결

	//// 숫자 2
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // 앞면 상단
	//LineTo(hDC, baseX + size, baseY + size / 2);     // 앞면 우측 상단
	//LineTo(hDC, baseX, baseY + size / 2);            // 앞면 중앙
	//LineTo(hDC, baseX, baseY + size);              // 앞면 좌측 하단
	//LineTo(hDC, baseX + size, baseY + size);       // 앞면 하단
	//// 윗면
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// 우측면
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// 숫자 3
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // 앞면 상단
	//LineTo(hDC, baseX + size, baseY + size);       // 앞면 우측
	//LineTo(hDC, baseX, baseY + size);              // 앞면 하단
	//MoveToEx(hDC, baseX, baseY + size / 2, NULL);
	//LineTo(hDC, baseX + size, baseY + size / 2);     // 앞면 중앙
	//// 윗면
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// 우측면
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// 숫자 4
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX, baseY + size / 2);            // 앞면 좌측
	//LineTo(hDC, baseX + size, baseY + size / 2);     // 앞면 중앙
	//MoveToEx(hDC, baseX + size * 2 / 3, baseY, NULL);
	//LineTo(hDC, baseX + size * 2 / 3, baseY + size);   // 앞면 우측 수직선
	//// 윗면
	//MoveToEx(hDC, baseX + size * 2 / 3, baseY, NULL);
	//LineTo(hDC, baseX + size * 2 / 3 + depth, baseY - depth);
	//// 우측면
	//LineTo(hDC, baseX + size * 2 / 3 + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size * 2 / 3, baseY + size);

	//// 숫자 5
	//baseX = 50;
	//baseY += gap;
	//MoveToEx(hDC, baseX + size, baseY, NULL);
	//LineTo(hDC, baseX, baseY);                     // 앞면 상단
	//LineTo(hDC, baseX, baseY + size / 2);            // 앞면 좌측 상단
	//LineTo(hDC, baseX + size, baseY + size / 2);     // 앞면 중앙
	//LineTo(hDC, baseX + size, baseY + size);       // 앞면 우측 하단
	//LineTo(hDC, baseX, baseY + size);              // 앞면 하단
	//// 윗면
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// 우측면
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// 숫자 6
	//baseX += gap;
	//MoveToEx(hDC, baseX + size, baseY, NULL);
	//LineTo(hDC, baseX, baseY);                     // 앞면 상단
	//LineTo(hDC, baseX, baseY + size);              // 앞면 좌측
	//LineTo(hDC, baseX + size, baseY + size);       // 앞면 하단
	//LineTo(hDC, baseX + size, baseY + size / 2);     // 앞면 우측 하단
	//LineTo(hDC, baseX, baseY + size / 2);            // 앞면 중앙
	//// 윗면
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// 우측면
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// 숫자 7
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // 앞면 상단
	//LineTo(hDC, baseX + size / 2, baseY + size);     // 앞면 대각선
	//// 윗면
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// 우측면
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size / 2 + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size / 2, baseY + size);

	//// 숫자 8
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // 앞면 상단
	//LineTo(hDC, baseX + size, baseY + size);       // 앞면 우측
	//LineTo(hDC, baseX, baseY + size);              // 앞면 하단
	//LineTo(hDC, baseX, baseY);                     // 앞면 좌측
	//MoveToEx(hDC, baseX, baseY + size / 2, NULL);
	//LineTo(hDC, baseX + size, baseY + size / 2);     // 앞면 중앙
	//// 윗면
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// 우측면
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// 숫자 9
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // 앞면 상단
	//LineTo(hDC, baseX + size, baseY + size);       // 앞면 우측
	//LineTo(hDC, baseX, baseY + size);              // 앞면 하단
	//MoveToEx(hDC, baseX, baseY + size / 2, NULL);
	//LineTo(hDC, baseX + size, baseY + size / 2);     // 앞면 중앙
	//LineTo(hDC, baseX, baseY);                     // 앞면 좌측 상단
	//// 윗면
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// 우측면
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	// 리소스 해제
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}