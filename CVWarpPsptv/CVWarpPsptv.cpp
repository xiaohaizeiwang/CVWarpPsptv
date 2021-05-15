// CVWarpPsptv.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "CVWarpPsptv.h"
#include "opencv2/opencv.hpp"
#include "WarpAlg.h"
using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CCVWarpPsptvApp

CCVWarpPsptv::CCVWarpPsptv()
{
	m_pAlg = new WarpAlg();
}

int CCVWarpPsptv::Free()
{
	if (m_pAlg)
	{
		delete m_pAlg;
		m_pAlg = NULL;
	}
	return 0;
}


int CCVWarpPsptv::cvGoodFeaturesToTrack(HObject &ho_hModelImg, HObject & ho_hMask, int iNumPoints, HTuple &hv_htRow, HTuple &hv_htColumn)
{
	return ((WarpAlg *)m_pAlg)->cvGoodFeaturesToTrack(ho_hModelImg, ho_hMask, iNumPoints, hv_htRow, hv_htColumn);
}
int CCVWarpPsptv::cvWarpPerspective(HObject &ho_hModelImg, HObject &ho_hCheckImg, HTuple &hv_htRow, HTuple &hv_htColumn)
{
	return ((WarpAlg *)m_pAlg)->cvWarpPerspective(ho_hModelImg, ho_hCheckImg, hv_htRow, hv_htColumn);
}

void CCVWarpPsptv::cvWarpPesPectiveImg(HObject &ho_hCheckImg)
{
	((WarpAlg *)m_pAlg)->cvWarpPesPectiveImg(ho_hCheckImg);
}
