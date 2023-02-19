
// MuftaDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMuftaDlg
class CMuftaDlg : public CDialogEx
{
// Создание
public:
	CMuftaDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUFTA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	double D;
	double d;
	double d1;
	double d2;
	double d3;
	double d4;
	double l;
	double l1;
	double l2;
	double b1;
	double b2;
	double h;
	double B;
	double D1;
	double R;	
	afx_msg void OnBnClickedCreate();
	void CheckData();
};
