#pragma once
#include "opencv2/opencv.hpp"
#include <opencv2\imgproc\types_c.h>
#include "Halcon.h"
#include "HalconCpp.h"
using namespace HalconCpp;
using namespace cv;
class WarpAlg
{
public:
	WarpAlg();
	~WarpAlg();
	int cvGoodFeaturesToTrack(HObject &ho_hModelImg, HObject & ho_hMask, int iNumPoints, HTuple &hv_htRow, HTuple &hv_htColumn);
	int cvWarpPerspective(HObject &ho_hModelImg, HObject &ho_hCheckImg, HTuple &hv_htRow, HTuple &hv_htColumn);
	void cvWarpPesPectiveImg(HObject &ho_hCheckImg);
private:
	Mat cvHomMat;
	Ptr<SparsePyrLKOpticalFlow > spOpt;
};