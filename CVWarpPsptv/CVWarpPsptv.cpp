// CVWarpPsptv.cpp : ���� DLL �ĳ�ʼ�����̡�
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
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
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
