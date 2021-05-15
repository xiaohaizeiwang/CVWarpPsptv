// CVWarpPsptv.h : CVWarpPsptv DLL ����ͷ�ļ�
//

#pragma once
#include "Halcon.h"
#include "HalconCpp.h"
using namespace HalconCpp;
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef CVWARPPSPTV_EXPORTS
#define CVWARPPSPTV_API __declspec(dllexport)
#else
#define CVWARPPSPTV_API __declspec(dllimport)
#endif


// CCVWarpPsptvApp
// �йش���ʵ�ֵ���Ϣ������� CVWarpPsptv.cpp
//

class CVWARPPSPTV_API CCVWarpPsptv
{
public:
	CCVWarpPsptv();
	int Free();
	int cvGoodFeaturesToTrack(HObject &ho_hModelImg, HObject & ho_hMask, int iNumPoints, HTuple &hv_htRow, HTuple &hv_htColumn);
	int cvWarpPerspective(HObject &ho_hModelImg, HObject &ho_hCheckImg, HTuple &hv_htRow, HTuple &hv_htColumn);
	void cvWarpPesPectiveImg(HObject &ho_hCheckImg);
// ��д
private:
	void* m_pAlg;
};
//�쳣����-1
