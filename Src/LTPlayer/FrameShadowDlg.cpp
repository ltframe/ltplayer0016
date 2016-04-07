// FrameShadowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LTPlayer.h"
#include "FrameShadowDlg.h"
#include "MusicUtils.h"

// FrameShadowDlg 对话框

IMPLEMENT_DYNAMIC(FrameShadowDlg, CDialog)

FrameShadowDlg::FrameShadowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FrameShadowDlg::IDD, pParent)
{
	Drawimage.LoadResImage(L"res\\nbgframe.png",L"BG",bgimgsrc);
}

FrameShadowDlg::~FrameShadowDlg()
{
}

void FrameShadowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FrameShadowDlg, CDialog)

	ON_WM_NCHITTEST()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// FrameShadowDlg 消息处理程序


BOOL FrameShadowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ModifyStyleEx(0,WS_EX_LAYERED);
	// TODO:  在此添加额外的初始化
	Drawimage.DrawMainBg(m_hWnd,MAINBG_WIDTH,MAINBG_HEIGHT,bgimgsrc,255);
	//Drawimage.DrawStaticImage(m_hWnd,18,98,0,0,271,67,bgroundimgsrc,255);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


LRESULT FrameShadowDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 SendMessage (WM_NCLBUTTONDOWN, HTCAPTION, 0);
	return CDialog::OnNcHitTest(point);
}


void FrameShadowDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
	CRect rect;
	rect.top=y;
	rect.left=x;
	rect.right=rect.left+MAINBG_WIDTH;
	rect.bottom=rect.top+MAINBG_HEIGHT;
	this->GetParent()->MoveWindow(&rect);
	// TODO: 在此处添加消息处理程序代码
}


BOOL FrameShadowDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基
	return MusicUtils::ArrestKeyDown(pMsg);
}
