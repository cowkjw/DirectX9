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
}

void CUiManager::RenderUi_CY(HDC hDC)
{
}

void CUiManager::RenderUi_DW(HDC hDC)
{
}

void CUiManager::RenderUi_JW(HDC hDC)
{
	// ���� ũ�� ������
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
		case FRUIT_TYPE::CHERRY:     // 3 * 2.0 = 6 ����
			vScale = {3.5f,3.5f,3.5f };  // ������
			break;
		case FRUIT_TYPE::ORANGE:     // 10 * 1.8 = 18 ����
			vScale = { 1.5f, 1.5f, 1.5f };
			break;
		case FRUIT_TYPE::LEMON:      // 15 * 1.6 = 24 ����
			vScale = { 1.5f, 1.5f, 1.5f };
			break;
		case FRUIT_TYPE::APPLE:      // 30 * 1.4 = 42 ����
			vScale = { 1.2f, 1.2f, 1.2f };
			break;
		case FRUIT_TYPE::PEACH:      // 35 * 1.2 = 42 ����
			vScale = { 1.2f, 1.2f, 1.2f };
			break;
		case FRUIT_TYPE::PINEAPPLE:  // 40 * 1.0 = 40 ����
			vScale = { 1.0f, 1.0f, 1.0f };
			break;
		case FRUIT_TYPE::MELON:      // 50 * 0.8 = 40 ����
			vScale = { 0.8f,0.8f,0.8f };
			break;
		case FRUIT_TYPE::PUMPKIN:    // 60 * 0.6 = 36 ����
			vScale = { 0.6f, 0.6f, 0.6f };
			break;
		case FRUIT_TYPE::WATERMELON: // 70 * 0.4 = 28 ����
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

			// �ش� �� ��ȯ
			D3DXVec3TransformCoord(&m_vecRenderPoints[i], &m_vecRenderPoints[i], &matWorld);
		}

		// ������ 
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
	int size = 30;    // ���� ũ��
	int depth = 10;   // ��ü���� ���� ����
	int gap = 50;     // ���� ����
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	//// ���� 0
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // �ո� ���
	//LineTo(hDC, baseX + size, baseY + size);       // �ո� ����
	//LineTo(hDC, baseX, baseY + size);              // �ո� �ϴ�
	//LineTo(hDC, baseX, baseY);                     // �ո� ����
	//// ����
	//LineTo(hDC, baseX + depth, baseY - depth);     // ���� ��� �缱
	//LineTo(hDC, baseX + size + depth, baseY - depth); // ���� ���
	//LineTo(hDC, baseX + size, baseY);              // ���� ��� �缱
	//// ������
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth); // ���� �缱
	//LineTo(hDC, baseX + size, baseY + size);       // ���� �ϴ� ����

	//// ���� 1
	baseX += gap;
	int midX = baseX + size / 2;
	MoveToEx(hDC, midX, baseY, NULL);
	LineTo(hDC, midX, baseY + size);               // �ո� ������
	// ����
	MoveToEx(hDC, midX, baseY, NULL);
	LineTo(hDC, midX + depth, baseY - depth);      // ��� �缱
	// ������
	LineTo(hDC, midX + depth, baseY + size - depth);
	LineTo(hDC, midX, baseY + size);               // �ϴ� ����

	//// ���� 2
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // �ո� ���
	//LineTo(hDC, baseX + size, baseY + size / 2);     // �ո� ���� ���
	//LineTo(hDC, baseX, baseY + size / 2);            // �ո� �߾�
	//LineTo(hDC, baseX, baseY + size);              // �ո� ���� �ϴ�
	//LineTo(hDC, baseX + size, baseY + size);       // �ո� �ϴ�
	//// ����
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// ������
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// ���� 3
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // �ո� ���
	//LineTo(hDC, baseX + size, baseY + size);       // �ո� ����
	//LineTo(hDC, baseX, baseY + size);              // �ո� �ϴ�
	//MoveToEx(hDC, baseX, baseY + size / 2, NULL);
	//LineTo(hDC, baseX + size, baseY + size / 2);     // �ո� �߾�
	//// ����
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// ������
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// ���� 4
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX, baseY + size / 2);            // �ո� ����
	//LineTo(hDC, baseX + size, baseY + size / 2);     // �ո� �߾�
	//MoveToEx(hDC, baseX + size * 2 / 3, baseY, NULL);
	//LineTo(hDC, baseX + size * 2 / 3, baseY + size);   // �ո� ���� ������
	//// ����
	//MoveToEx(hDC, baseX + size * 2 / 3, baseY, NULL);
	//LineTo(hDC, baseX + size * 2 / 3 + depth, baseY - depth);
	//// ������
	//LineTo(hDC, baseX + size * 2 / 3 + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size * 2 / 3, baseY + size);

	//// ���� 5
	//baseX = 50;
	//baseY += gap;
	//MoveToEx(hDC, baseX + size, baseY, NULL);
	//LineTo(hDC, baseX, baseY);                     // �ո� ���
	//LineTo(hDC, baseX, baseY + size / 2);            // �ո� ���� ���
	//LineTo(hDC, baseX + size, baseY + size / 2);     // �ո� �߾�
	//LineTo(hDC, baseX + size, baseY + size);       // �ո� ���� �ϴ�
	//LineTo(hDC, baseX, baseY + size);              // �ո� �ϴ�
	//// ����
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// ������
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// ���� 6
	//baseX += gap;
	//MoveToEx(hDC, baseX + size, baseY, NULL);
	//LineTo(hDC, baseX, baseY);                     // �ո� ���
	//LineTo(hDC, baseX, baseY + size);              // �ո� ����
	//LineTo(hDC, baseX + size, baseY + size);       // �ո� �ϴ�
	//LineTo(hDC, baseX + size, baseY + size / 2);     // �ո� ���� �ϴ�
	//LineTo(hDC, baseX, baseY + size / 2);            // �ո� �߾�
	//// ����
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// ������
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// ���� 7
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // �ո� ���
	//LineTo(hDC, baseX + size / 2, baseY + size);     // �ո� �밢��
	//// ����
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// ������
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size / 2 + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size / 2, baseY + size);

	//// ���� 8
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // �ո� ���
	//LineTo(hDC, baseX + size, baseY + size);       // �ո� ����
	//LineTo(hDC, baseX, baseY + size);              // �ո� �ϴ�
	//LineTo(hDC, baseX, baseY);                     // �ո� ����
	//MoveToEx(hDC, baseX, baseY + size / 2, NULL);
	//LineTo(hDC, baseX + size, baseY + size / 2);     // �ո� �߾�
	//// ����
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// ������
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	//// ���� 9
	//baseX += gap;
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + size, baseY);              // �ո� ���
	//LineTo(hDC, baseX + size, baseY + size);       // �ո� ����
	//LineTo(hDC, baseX, baseY + size);              // �ո� �ϴ�
	//MoveToEx(hDC, baseX, baseY + size / 2, NULL);
	//LineTo(hDC, baseX + size, baseY + size / 2);     // �ո� �߾�
	//LineTo(hDC, baseX, baseY);                     // �ո� ���� ���
	//// ����
	//MoveToEx(hDC, baseX, baseY, NULL);
	//LineTo(hDC, baseX + depth, baseY - depth);
	//LineTo(hDC, baseX + size + depth, baseY - depth);
	//LineTo(hDC, baseX + size, baseY);
	//// ������
	//MoveToEx(hDC, baseX + size + depth, baseY - depth, NULL);
	//LineTo(hDC, baseX + size + depth, baseY + size - depth);
	//LineTo(hDC, baseX + size, baseY + size);

	// ���ҽ� ����
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}