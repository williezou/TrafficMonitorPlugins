﻿// OptionsContainerDlg.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "TextReader.h"
#include "OptionsContainerDlg.h"
#include "DataManager.h"

// COptionsContainerDlg 对话框

IMPLEMENT_DYNAMIC(COptionsContainerDlg, CDialog)

COptionsContainerDlg::COptionsContainerDlg(int tab_selected, CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_OPTIONS_CONTAINER_DLG, pParent),
    m_tab_selected(tab_selected)
{

}

COptionsContainerDlg::~COptionsContainerDlg()
{
}

void COptionsContainerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB1, m_tab_ctrl);
}


BEGIN_MESSAGE_MAP(COptionsContainerDlg, CDialog)
    ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// COptionsContainerDlg 消息处理程序


void COptionsContainerDlg::OnOK()
{
    // TODO: 在此添加专用代码和/或调用基类
    m_options_dlg.OnOK();
    m_chapter_dlg.OnOK();
    m_bookmark_dlg.OnOK();

    CDialog::OnOK();
}


BOOL COptionsContainerDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    HICON hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, g_data.DPI(16), g_data.DPI(16), 0);
    SetIcon(hIcon, FALSE);
    
    //获取初始时的大小
    CRect rect;
    GetWindowRect(rect);
    m_min_size = rect.Size();

    //创建子对话框
    m_options_dlg.Create(IDD_OPTIONS_DIALOG, &m_tab_ctrl);
    m_chapter_dlg.Create(IDD_CHAPTER_DIALOG, &m_tab_ctrl);
    m_bookmark_dlg.Create(IDD_BOOKMARK_DLG, &m_tab_ctrl);


    //添加对话框
    m_tab_ctrl.AddWindow(&m_options_dlg, g_data.StringRes(IDS_SETTINGS));
    m_tab_ctrl.AddWindow(&m_chapter_dlg, g_data.StringRes(IDS_CHAPTERS));
    m_tab_ctrl.AddWindow(&m_bookmark_dlg, g_data.StringRes(IDS_BOOKMARK));
    m_bookmark_dlg.AdjustColumeWidth();

    //设置默认选中的标签
    if (m_tab_selected < 0 || m_tab_selected >= m_tab_ctrl.GetItemCount())
        m_tab_selected = 0;
    m_tab_ctrl.SetCurTab(m_tab_selected);


    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}


void COptionsContainerDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    //限制窗口最小大小
    lpMMI->ptMinTrackSize.x = m_min_size.cx;
    lpMMI->ptMinTrackSize.y = m_min_size.cy;

    CDialog::OnGetMinMaxInfo(lpMMI);
}
