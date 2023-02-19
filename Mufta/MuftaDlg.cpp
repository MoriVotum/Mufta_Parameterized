// MuftaDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Mufta.h"
#include "MuftaDlg.h"
#include "afxdialogex.h"

#include "math.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\ksConstants3D.h"

#include <atlsafe.h>
#include <comutil.h>

#define PI 3.14159265358979323846

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#import "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\lib\kAPI5.tlb"

using namespace Kompas6API5;

KompasObjectPtr pKompasApp5;
ksPartPtr pPart;
ksDocument3DPtr pDoc;


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CMuftaDlg


CMuftaDlg::CMuftaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MUFTA_DIALOG, pParent)
	, D(80)
	, d(16)
	, d1(20)
	, d2(25)
	, d3(8.4)
	, d4(9)
	, l(25)
	, l1(8)
	, l2(2)
	, b1(1)
	, b2(0.5)
	, h(18.3)
	, B(4)
	, D1(55)
	, R(0.2)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMuftaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_D_BIG, D);
	DDX_Text(pDX, IDC_EDIT_D_SMALL, d);
	DDX_Text(pDX, IDC_EDIT_D1, d1);
	DDX_Text(pDX, IDC_EDIT_D2, d2);
	DDX_Text(pDX, IDC_EDIT_D3, d3);
	DDX_Text(pDX, IDC_EDIT_D4, d4);
	DDX_Text(pDX, IDC_EDIT_L, l);
	DDX_Text(pDX, IDC_EDIT_L1, l1);
	DDX_Text(pDX, IDC_EDIT_L2, l2);
	DDX_Text(pDX, IDC_EDIT_B1, b1);
	DDX_Text(pDX, IDC_EDIT_B2, b2);
	DDX_Text(pDX, IDC_EDIT_H, h);
	DDX_Text(pDX, IDC_EDIT_B, B);
	DDX_Text(pDX, IDC_EDIT_D_BIG_1, D1);
	DDX_Text(pDX, IDC_EDIT_R, R);	
}

BEGIN_MESSAGE_MAP(CMuftaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCREATE, &CMuftaDlg::OnBnClickedCreate)
END_MESSAGE_MAP()


// Обработчики сообщений CMuftaDlg

BOOL CMuftaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMuftaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMuftaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMuftaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMuftaDlg::OnBnClickedCreate()
{
	// TODO: добавьте свой код обработчика уведомлений
	BeginWaitCursor();

	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	/*DeleteFile(L"D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\detail.m3d");*/

	// take data from edit boxes
	
	CString str;
	GetDlgItemText(IDC_EDIT_D_BIG, str);
	D = _wtof(str);
	GetDlgItemText(IDC_EDIT_D_SMALL, str);
	d = _wtof(str);
	GetDlgItemText(IDC_EDIT_D1, str);
	d1 = _wtof(str);
	GetDlgItemText(IDC_EDIT_D2, str);
	d2 = _wtof(str);
	GetDlgItemText(IDC_EDIT_D3, str);
	d3 = _wtof(str);
	GetDlgItemText(IDC_EDIT_D4, str);
	d4 = _wtof(str);
	GetDlgItemText(IDC_EDIT_D_BIG_1, str);
	D1 = _wtof(str);
	GetDlgItemText(IDC_EDIT_L, str);
	l = _wtof(str);
	GetDlgItemText(IDC_EDIT_L1, str);
	l1 = _wtof(str);
	GetDlgItemText(IDC_EDIT_L2, str);
	l2 = _wtof(str);
	GetDlgItemText(IDC_EDIT_B1, str);
	b1 = _wtof(str);
	GetDlgItemText(IDC_EDIT_B2, str);
	b2 = _wtof(str);
	GetDlgItemText(IDC_EDIT_H, str);
	h = _wtof(str);
	GetDlgItemText(IDC_EDIT_B, str);
	B = _wtof(str);
	GetDlgItemText(IDC_EDIT_R, str);
	R = _wtof(str);
	
	if (D <= 0)
	{
		MessageBox(L"Введите большой диаметр детали");
		Sleep(1000);
		return;
	}
	if (d > D)
	{
		MessageBox(L"Малый диаметр не может быть больше большого");
		Sleep(1000);
		return;
	}
	if (d <= 0)
	{
		MessageBox(L"Введите малый диаметр детали");
		Sleep(1000);
		return;
	}
	if (d1 <= 0)
	{
		MessageBox(L"Введите диаметр отверстия d1");
		Sleep(1000);
		return;
	}
	if (d2 <= 0)
	{
		MessageBox(L"Введите диаметр отверстия d2");
		Sleep(1000);
		return;
	}
	if (d3 <= 0)
	{
		MessageBox(L"Введите диаметр отверстия d3");
		Sleep(1000);
		return;
	}
	if (d4 <= 0)
	{
		MessageBox(L"Введите диаметр отверстия d4");
		Sleep(1000);
		return;
	}
	if (l <= 0)
	{
		MessageBox(L"Введите длину детали");
		Sleep(1000);
		return;
	}
	if (l1 <= 0)
	{
		MessageBox(L"Введите длину отверстия l1");
		Sleep(1000);
		return;
	}
	if (l2 <= 0)
	{
		MessageBox(L"Введите длину отверстия l2");
		Sleep(1000);
		return;
	}
	if (b1 <= 0)
	{
		MessageBox(L"Введите ширину отверстия b1");
		Sleep(1000);
		return;
	}
	if (b2 <= 0)
	{
		MessageBox(L"Введите ширину отверстия b2");
		Sleep(1000);
		return;
	}
	if (h <= 0)
	{
		MessageBox(L"Введите высоту детали");
		Sleep(1000);
		return;
	}
	if (B <= 0)
	{
		MessageBox(L"Введите ширину детали");
		Sleep(1000);
		return;
	}
	if (D1 <= 0)
	{
		MessageBox(L"Введите диаметр отверстия D1");
		Sleep(1000);
		return;
	}
	if (R <= 0)
	{
		MessageBox(L"Введите радиус скругления");
		Sleep(1000);
		return;
	}
	if (d > d1)
	{
		MessageBox(L"Диаметр отверстия d не может быть больше малого диаметра d1");
		Sleep(1000);
		return;
	}
	if (d > d2)
	{
		MessageBox(L"Диаметр отверстия d не может быть больше малого диаметра d2");
		Sleep(1000);
		return;
	}
	if (l1 > l)
	{
		MessageBox(L"Длина отверстия l1 не может быть больше длины детали l");
		Sleep(1000);
		return;
	}
	if (l2 > l1)
	{
		MessageBox(L"Длина отверстия l2 не может быть больше длины детали l1");
		Sleep(1000);
		return;
	}
	if (D / d < 5)
	{
		MessageBox(L"Диаметр отверстия d не может быть меньше 1/5 от большого диаметра D");
		Sleep(1000);
		return;
	}
	if (d2 < d)
	{
		MessageBox(L"Диаметр отверстия d2 не может быть меньше диаметра d");
		Sleep(1000);
		return;
	}
	if (R > B / 2)
	{
		MessageBox(L"Скругления не могут превышать размеры шпонки");
		Sleep(1000);
		return;
	}

	pKompasApp5->Visible = true;
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	// Общий контур
	
	ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch->Create();

	ksDocument2DPtr pDoc2D = pSketchDef->BeginEdit();

	double point[8][2];
	point[0][0] = 0;
	point[0][1] = D / 2.f;
	point[1][0] = l1;
	point[1][1] = D / 2.f;
	point[2][0] = l1;
	point[2][1] = d1 / 2.f;
	point[3][0] = l;
	point[3][1] = d1 / 2.f;
	point[4][0] = l;
	point[4][1] = d / 2.f;
	point[5][0] = l2;
	point[5][1] = d / 2.f;
	point[6][0] = l2;
	point[6][1] = d2 / 2.f;
	point[7][0] = 0;
	point[7][1] = d2 / 2.f;

	pDoc2D->ksLineSeg(point[0][0], point[0][1], point[1][0], point[1][1], 1);
	pDoc2D->ksLineSeg(point[1][0], point[1][1], point[2][0], point[2][1], 1);
	pDoc2D->ksLineSeg(point[2][0], point[2][1], point[3][0], point[3][1], 1);
	pDoc2D->ksLineSeg(point[3][0], point[3][1], point[4][0], point[4][1], 1);
	pDoc2D->ksLineSeg(point[4][0], point[4][1], point[5][0], point[5][1], 1);
	pDoc2D->ksLineSeg(point[5][0], point[5][1], point[6][0], point[6][1], 1);
	pDoc2D->ksLineSeg(point[6][0], point[6][1], point[7][0], point[7][1], 1);
	pDoc2D->ksLineSeg(point[7][0], point[7][1], point[0][0], point[0][1], 1);
	
	pDoc2D->ksLineSeg(l + 5, 0, l + 10, 0, 3); // ось X
	
	pSketchDef->EndEdit();

	// Вращение
	
	ksEntityPtr pRotate = pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotateDef = pRotate->GetDefinition();
	pRotateDef->SetSketch(pSketch);
	pRotateDef->SetSideParam(TRUE, 360);
	pRotate->Create();

	// Добавление двух отверстий

	pSketch = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pSketch->Create();
	
	pDoc2D = pSketchDef->BeginEdit();
	pDoc2D->ksCircle(D1 / 2.f, 0, d4 / 2.f, 1); // большое отверстие
	pDoc2D->ksCircle(-D1 / 2.f, 0, d3 / 2.f, 1); // маленькое отверстие
	pSketchDef->EndEdit();

	ksEntityPtr pExtrude = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pExtrudeDef = pExtrude->GetDefinition();
	
	pExtrudeDef->directionType = dtNormal;
	pExtrudeDef->SetSketch(pSketch);
	pExtrudeDef->SetSideParam(true, etThroughAll, 0, 0, false);
	pExtrude->Create();
	
	// добавление фасок на отверстия

	ksEntityCollectionPtr fledges = pPart->EntityCollection(o3d_edge);
	
	ksEntityPtr pChamfer = pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamferDef = pChamfer->GetDefinition();
	pChamferDef->SetChamferParam(true, b2, b2);
	ksEntityCollectionPtr pChamferEdges = pChamferDef->array();
	pChamferEdges->Clear();

	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr pEdge = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr pEdgeDef = pEdge->GetDefinition();
		
		if (pEdgeDef->GetOwnerEntity() == pExtrude) {
			if (pEdgeDef->IsCircle()) {
				ksVertexDefinitionPtr pVertexDef1 = pEdgeDef->GetVertex(true);
				double x1, y1, z1;
				pVertexDef1->GetPoint(&x1, &y1, &z1);

				if (x1 > 0)
					pChamferEdges->Add(pEdge);

				if (x1 == 0) {
					ksFaceDefinitionPtr pFaceDef = pEdgeDef->GetAdjacentFace(true);
					ksEntityPtr pFace = pFaceDef->GetEntity();

					pFace->Putname("face-back");
					pFace->Update();
				} 
				if (x1 == l1) {
					ksFaceDefinitionPtr pFaceDef = pEdgeDef->GetAdjacentFace(true);
					ksEntityPtr pFace = pFaceDef->GetEntity();

					pFace->Putname("face-front");
					pFace->Update();
				}
			}
		}
	}

	pChamfer->Create();
	
	// добавление фасок на края
	
	pChamfer = pPart->NewEntity(o3d_chamfer);
	pChamferDef = pChamfer->GetDefinition();
	pChamferDef->SetChamferParam(true, b1, b1);

	pChamferEdges = pChamferDef->array();
	pChamferEdges->Clear();

	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr pEdge = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr pEdgeDef = pEdge->GetDefinition();
		
		if (pEdgeDef->GetOwnerEntity() == pRotate) {
			if (pEdgeDef->IsCircle()) {
				ksVertexDefinitionPtr pVertexDef1 = pEdgeDef->GetVertex(true);
				double x1, y1, z1;
				pVertexDef1->GetPoint(&x1, &y1, &z1);

				if (y1 == D / 2.f || x1 == l)
					pChamferEdges->Add(pEdge);
			}
		}
	}
	
	pChamfer->Create();

	ksEntityCollectionPtr pFaces = pPart->EntityCollection(o3d_face);
	for (int i = 0; i < pFaces->GetCount(); i++) {
		ksEntityPtr pFace = pFaces->GetByIndex(i);
		ksFaceDefinitionPtr pFaceDef = pFace->GetDefinition();

		if (pFaceDef->GetOwnerEntity() == pExtrude) {
			if (pFaceDef->IsCylinder()) {
				double h, r;
				pFaceDef->GetCylinderParam(&h, &r);

				if (r == d3 / 2.f) {
					pFace->Putname("top-hole");
					pFace->Update();
				}
				if (r == d4 / 2.f) {
					pFace->Putname("bottom-hole");
					pFace->Update();
				}
			}
		}
	}

	// Делаем Паз
	
	pSketch = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pSketch->Create();
	
	pDoc2D = pSketchDef->BeginEdit();
	
	double point1[4][2];
	point1[0][0] = -h / 2;
	point1[0][1] = -B / 2.f;
	point1[1][0] = -h / 2;
	point1[1][1] = B / 2.f;
	point1[2][0] = 0;
	point1[2][1] = B / 2.f;
	point1[3][0] = 0;
	point1[3][1] = -B / 2.f;
	
	pDoc2D->ksLineSeg(point1[0][0], point1[0][1], point1[1][0], point1[1][1], 1);
	pDoc2D->ksLineSeg(point1[1][0], point1[1][1], point1[2][0], point1[2][1], 1);
	pDoc2D->ksLineSeg(point1[2][0], point1[2][1], point1[3][0], point1[3][1], 1);
	pDoc2D->ksLineSeg(point1[3][0], point1[3][1], point1[0][0], point1[0][1], 1);
	
	pSketchDef->EndEdit();

	pExtrude = pPart->NewEntity(o3d_cutExtrusion);
	pExtrudeDef = pExtrude->GetDefinition();
	
	pExtrudeDef->directionType = dtNormal;
	pExtrudeDef->SetSketch(pSketch);
	pExtrudeDef->SetSideParam(true, etThroughAll, 0, 0, false);
	
	pExtrude->Create();

	// Скругление в пазу - НЕ РАБОТАЕТ
	fledges = pPart->EntityCollection(o3d_edge);
	
	ksEntityPtr pFillet = pPart->NewEntity(o3d_fillet);
	ksFilletDefinitionPtr pFilletDef = pFillet->GetDefinition();
	pFilletDef->radius = R;
	ksEntityCollectionPtr pFilletEdges = pFilletDef->array();
	pFilletEdges->Clear();

	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr pEdge = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr pEdgeDef = pEdge->GetDefinition();

		if (pEdgeDef->GetOwnerEntity() == pExtrude) {
			ksVertexDefinitionPtr pVertexDef1 = pEdgeDef->GetVertex(true);
			ksVertexDefinitionPtr pVertexDef2 = pEdgeDef->GetVertex(false);
			double x1, y1, z1, x2, y2, z2;
			pVertexDef1->GetPoint(&x1, &y1, &z1);
			pVertexDef2->GetPoint(&x2, &y2, &z2);

			if (z1 > (d / 2.f) && abs(y1 - y2) == 0)
				pFilletEdges->Add(pEdge);
		}
	}

	pFillet->Create();

	pDoc->SaveAs("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\deatil.m3d");
	pDoc->close();

	// Делаем болт - палка

	double mSize = round(min(d3, d4));
	double dSize = min(d3, d4) + 9;
	double sSize = dSize - 2;
	double hSize = round(round(dSize + 1) / 3) + 1;
	
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	pSketch = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch->Create();
	pDoc2D = pSketchDef->BeginEdit();
	
	double point2[4][2];
	point2[0][0] = 0;
	point2[0][1] = 0;
	point2[1][0] = mSize / 2;
	point2[1][1] = 0;
	point2[2][0] = mSize / 2;
	point2[2][1] = l1 * 2 + hSize;
	point2[3][0] = 0;
	point2[3][1] = l1 * 2 + hSize;
	
	pDoc2D->ksLineSeg(point2[0][0], point2[0][1], point2[1][0], point2[1][1], 1);
	pDoc2D->ksLineSeg(point2[1][0], point2[1][1], point2[2][0], point2[2][1], 1);
	pDoc2D->ksLineSeg(point2[2][0], point2[2][1], point2[3][0], point2[3][1], 1);
	pDoc2D->ksLineSeg(point2[3][0], point2[3][1], point2[0][0], point2[0][1], 1);
	
	pDoc2D->ksLineSeg(0, l1 * 2 + hSize + 5, 0, l1 * 2 + hSize + 10, 3);

	pSketchDef->EndEdit();
	
	pRotate = pPart->NewEntity(o3d_bossRotated);
	pRotateDef = pRotate->GetDefinition();
	pRotateDef->SetSketch(pSketch);
	pRotateDef->SetSideParam(TRUE, 360);
	pRotate->Create();

	// Называем ногу

	fledges = pPart->EntityCollection(o3d_edge);

	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr pEdge = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr pEdgeDef = pEdge->GetDefinition();

		if (pEdgeDef->GetOwnerEntity() == pRotate) {
			if (pEdgeDef->IsCircle()) {
				ksVertexDefinitionPtr pVertexDef1 = pEdgeDef->GetVertex(true);
				double x1, y1, z1;
				pVertexDef1->GetPoint(&x1, &y1, &z1);

				if (y1 == l1 * 2 + hSize) {
					ksFaceDefinitionPtr pFaceDef = pEdgeDef->GetAdjacentFace(true);
					ksEntityPtr pFace = pFaceDef->GetEntity();

					pFace->Putname("bolt-leg");
					pFace->Update();

					pFaceDef = pEdgeDef->GetAdjacentFace(false);
					pFace = pFaceDef->GetEntity();

					pFace->Putname("bolt-head");
					pFace->Update();
				}
				
				if (y1 == 0) {
					ksFaceDefinitionPtr pFaceDef = pEdgeDef->GetAdjacentFace(true);
					ksEntityPtr pFace = pFaceDef->GetEntity();
					
					pFace->Putname("bolt-bottom");
					pFace->Update();
				}
			}
		}
	}

	// шапка болта

	pSketch = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pSketch->Create();
	pDoc2D = pSketchDef->BeginEdit();

	double point3[6][2];
	
	point3[0][0] = 0;
	point3[0][1] = -dSize / 2;
	point3[1][0] = -sSize / 2;
	point3[1][1] = -tan(PI/6) * sSize / 2;
	point3[2][0] = -sSize / 2;
	point3[2][1] = tan(PI / 6) * sSize / 2;
	point3[3][0] = 0;
	point3[3][1] = dSize / 2;
	point3[4][0] = sSize / 2;
	point3[4][1] = tan(PI / 6) * sSize / 2;
	point3[5][0] = sSize / 2;
	point3[5][1] = -tan(PI / 6) * sSize / 2;

	pDoc2D->ksLineSeg(point3[0][0], point3[0][1], point3[1][0], point3[1][1], 1);
	pDoc2D->ksLineSeg(point3[1][0], point3[1][1], point3[2][0], point3[2][1], 1);
	pDoc2D->ksLineSeg(point3[2][0], point3[2][1], point3[3][0], point3[3][1], 1);
	pDoc2D->ksLineSeg(point3[3][0], point3[3][1], point3[4][0], point3[4][1], 1);
	pDoc2D->ksLineSeg(point3[4][0], point3[4][1], point3[5][0], point3[5][1], 1);
	pDoc2D->ksLineSeg(point3[5][0], point3[5][1], point3[0][0], point3[0][1], 1);
	
	pSketchDef->EndEdit();
	
	ksEntityPtr pExtrudeBolt = pPart->NewEntity(o3d_baseExtrusion);
	ksBaseExtrusionDefinitionPtr pBaseDef = pExtrudeBolt->GetDefinition();
	pBaseDef->directionType = dtReverse;
	pBaseDef->SetSketch(pSketch);
	pBaseDef->SetSideParam(false, etBlind, hSize, 0, false);
	pExtrudeBolt->Create();
	
	// называем малыша
	/*ksEntityCollectionPtr fledgesBolt = pPart->EntityCollection(o3d_edge);

	for (int i = 0; i < fledgesBolt->GetCount(); i++) {
		ksEntityPtr pEdge = fledgesBolt->GetByIndex(i);
		ksEdgeDefinitionPtr pEdgeDef = pEdge->GetDefinition();

		if (pEdgeDef->GetOwnerEntity() == pExtrudeBolt) {
			ksVertexDefinitionPtr pVertexDef1 = pEdgeDef->GetVertex(true);
			double x1, y1, z1;
			pVertexDef1->GetPoint(&x1, &y1, &z1);

			if (x1 == 0)
			{
				ksFaceDefinitionPtr pFaceDef = pEdgeDef->GetAdjacentFace(true);
				ksEntityPtr pFace = pFaceDef->GetEntity();

				pFace->Putname("bolt-bottom");
				pFace->Update();
			}
		}
	}*/

	pDoc->SaveAs("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\bolt.m3d");
	pDoc->close();

	// Делаем шайбу
	
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	pSketch = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch->Create();
	pDoc2D = pSketchDef->BeginEdit();
	
	double point4[4][2];
	
	point4[0][0] = mSize / 2 + 0.5;
	point4[0][1] = 0;
	point4[1][0] = mSize / 2 + 0.5;
	point4[1][1] = hSize;
	point4[2][0] = dSize / 2;
	point4[2][1] = hSize;
	point4[3][0] = dSize / 2;
	point4[3][1] = 0;
	
	pDoc2D->ksLineSeg(point4[0][0], point4[0][1], point4[1][0], point4[1][1], 1);
	pDoc2D->ksLineSeg(point4[1][0], point4[1][1], point4[2][0], point4[2][1], 1);
	pDoc2D->ksLineSeg(point4[2][0], point4[2][1], point4[3][0], point4[3][1], 1);
	pDoc2D->ksLineSeg(point4[3][0], point4[3][1], point4[0][0], point4[0][1], 1);

	pDoc2D->ksLineSeg(0, 5, 0, 10, 3);
	
	pSketchDef->EndEdit();

	pRotate = pPart->NewEntity(o3d_bossRotated);
	pRotateDef = pRotate->GetDefinition();
	pRotateDef->SetSketch(pSketch);
	pRotateDef->SetSideParam(TRUE, 360);
	pRotate->Create();

	fledges = pPart->EntityCollection(o3d_edge);
	
	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr pEdge = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr pEdgeDef = pEdge->GetDefinition();

		if (pEdgeDef->GetOwnerEntity() == pRotate) {
			if (pEdgeDef->IsCircle()) {
				ksVertexDefinitionPtr pVertexDef1 = pEdgeDef->GetVertex(true);
				double x1, y1, z1;
				pVertexDef1->GetPoint(&x1, &y1, &z1);

				if (y1 == 0 && x1 == dSize / 2)
				{
					ksFaceDefinitionPtr pFaceDef = pEdgeDef->GetAdjacentFace(true);
					ksEntityPtr pFace = pFaceDef->GetEntity();

					pFace->Putname("nut-top");
					pFace->Update();

					pFaceDef = pEdgeDef->GetAdjacentFace(false);
					pFace = pFaceDef->GetEntity();

					pFace->Putname("nut-leg");
					pFace->Update();
				}
			}
		}
	}

	pDoc->SaveAs("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\nut.m3d");
	pDoc->close();
	
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, false);
	pPart = pDoc->GetPart(pTop_Part);
	
	ksPartPtr pDeatial[6];
	pDoc->SetPartFromFile("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\deatil.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\deatil.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\bolt.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\bolt.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\nut.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\nut.m3d", pPart, true);

	pDeatial[0] = pDoc->GetPart(0);
	pDeatial[1] = pDoc->GetPart(1);
	pDeatial[2] = pDoc->GetPart(2);
	pDeatial[3] = pDoc->GetPart(3);
	pDeatial[4] = pDoc->GetPart(4);
	pDeatial[5] = pDoc->GetPart(5);

	ksEntityPtr pDetailTopHole[2];
	ksEntityPtr pDetailBottomHole[2];
	ksEntityPtr pDetailFace[2];
	ksEntityPtr pDetailFaceToBolt[2];
	ksEntityPtr pDetailBoltLeg[2];
	ksEntityPtr pDetailBoltHead[2];
	ksEntityPtr pDetailNutLeg[2];
	ksEntityPtr pDetailNutHead[2];

	for (int i = 0; i < 2; i++)
	{
		ksEntityCollectionPtr pDeatialFaces = pDeatial[i]->EntityCollection(o3d_face);

		pDetailTopHole[i] = pDeatialFaces->GetByName("top-hole", true, true);
		pDetailBottomHole[i] = pDeatialFaces->GetByName("bottom-hole", true, true);
		pDetailFace[i] = pDeatialFaces->GetByName("face-back", true, true);
		pDetailFaceToBolt[i] = pDeatialFaces->GetByName("face-front", true, true);
	}

	for (int i = 2; i < 4; i++)
	{
		ksEntityCollectionPtr pDeatialFaces = pDeatial[i]->EntityCollection(o3d_face);
		pDetailBoltLeg[i - 2] = pDeatialFaces->GetByName("bolt-leg", true, true);
		pDetailBoltHead[i - 2] = pDeatialFaces->GetByName("bolt-head", true, true);
	}

	for (int i = 4; i < 6; i++)
	{
		ksEntityCollectionPtr pDeatialFaces = pDeatial[i]->EntityCollection(o3d_face);
		pDetailNutLeg[i - 4] = pDeatialFaces->GetByName("nut-leg", true, true);
		pDetailNutHead[i - 4] = pDeatialFaces->GetByName("nut-top", true, true);
	}

	pDoc->AddMateConstraint(mc_Concentric, pDetailTopHole[0], pDetailTopHole[1], -1, 1, 0);
	pDoc->AddMateConstraint(mc_Concentric, pDetailBottomHole[0], pDetailBottomHole[1], -1, 1, 0);
	pDoc->AddMateConstraint(mc_Coincidence, pDetailFace[0], pDetailFace[1], -1, 1, 0);
	
	pDoc->AddMateConstraint(mc_Concentric, pDetailBoltLeg[0], pDetailTopHole[0], -1, 1, 0);
	pDoc->AddMateConstraint(mc_Concentric, pDetailBoltLeg[1], pDetailBottomHole[0], -1, 1, 0);

	pDoc->AddMateConstraint(mc_Distance, pDetailBoltHead[0], pDetailFaceToBolt[1], 1, 1, -hSize);
	pDoc->AddMateConstraint(mc_Distance, pDetailBoltHead[1], pDetailFaceToBolt[1], 1, 1, -hSize);

	pDoc->AddMateConstraint(mc_Concentric, pDetailNutLeg[0], pDetailTopHole[1], 1, 1, 0);
	pDoc->AddMateConstraint(mc_Concentric, pDetailNutLeg[1], pDetailBottomHole[1], 1, 1, 0);

	pDoc->AddMateConstraint(mc_Coincidence, pDetailNutHead[0], pDetailFaceToBolt[1], -1, 1, 0);
	pDoc->AddMateConstraint(mc_Coincidence, pDetailNutHead[1], pDetailFaceToBolt[1], -1, 1, 0);
	
	pDoc->RebuildDocument();

	pDoc->SaveAs("D:\\Works\\Code_Polytech\\Course_2\\Mufta\\Products\\mufta.3d");
}
