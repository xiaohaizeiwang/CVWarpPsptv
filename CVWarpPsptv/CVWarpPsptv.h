// CVWarpPsptv.h : CVWarpPsptv DLL 的主头文件
//

#pragma once
#include "Halcon.h"
#include "HalconCpp.h"
using namespace HalconCpp;
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#ifdef CVWARPPSPTV_EXPORTS
#define CVWARPPSPTV_API __declspec(dllexport)
#else
#define CVWARPPSPTV_API __declspec(dllimport)
#endif


// CCVWarpPsptvApp
// 有关此类实现的信息，请参阅 CVWarpPsptv.cpp
//

class CVWARPPSPTV_API CCVWarpPsptv
{
public:
	CCVWarpPsptv();
	int Free();
	int cvGoodFeaturesToTrack(HObject &ho_hModelImg, HObject & ho_hMask, int iNumPoints, HTuple &hv_htRow, HTuple &hv_htColumn);
	int cvWarpPerspective(HObject &ho_hModelImg, HObject &ho_hCheckImg, HTuple &hv_htRow, HTuple &hv_htColumn);
	void cvWarpPesPectiveImg(HObject &ho_hCheckImg);
// 重写
private:
	void* m_pAlg;
};
//异常返回-1
