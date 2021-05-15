#include "stdafx.h"
#include "WarpAlg.h"


WarpAlg::WarpAlg()
{
	spOpt = SparsePyrLKOpticalFlow::create(Size(21, 21), 0, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 200, 0.0001), 1,5);
}
int WarpAlg::cvGoodFeaturesToTrack(HObject &ho_hModelImg, HObject & ho_hMask, int iNumPoints, HTuple &hv_htRow, HTuple &hv_htColumn)
{
	HObject ho_hMaskImg;
	HTuple hv_htModelImgPtr, hv_htMaskImgPtr, hv_htWidth, hv_htHeight;//
	try
	{
		GetImagePointer1(ho_hModelImg, &hv_htModelImgPtr, nullptr, &hv_htWidth, &hv_htHeight);

		GenImageConst(&ho_hMaskImg, "byte", hv_htWidth, hv_htHeight);
		Union1(ho_hMask, &ho_hMask);
		PaintRegion(ho_hMask, ho_hMaskImg, &ho_hMaskImg, 255, "fill");
		GetImagePointer1(ho_hMaskImg, &hv_htMaskImgPtr, nullptr, nullptr, nullptr);

		Mat cvModelImg, cvMaskImg;
		std::vector<Point2f> prevPts;
		
		cvModelImg = Mat(hv_htHeight[0].L(), hv_htWidth[0].L(), CV_8UC1, (char *)hv_htModelImgPtr[0].L());
		cvMaskImg = Mat(hv_htHeight[0].L(), hv_htWidth[0].L(), CV_8UC1, (char *)hv_htMaskImgPtr[0].L());
		goodFeaturesToTrack(cvModelImg, prevPts, iNumPoints, 0.1, 5, cvMaskImg, 3, false, 0.04);

		if (prevPts.size() < 4)return -1;

		TupleGenConst(0, 0, &hv_htRow);
		TupleGenConst(0, 0, &hv_htColumn);
		for (int i = 0; i < prevPts.size(); i++)
		{
			hv_htColumn.Append(prevPts[i].x);
			hv_htRow.Append(prevPts[i].y);
		}
	}
	catch (...)
	{
		return -1;
	}
	//cornerSubPix(cvModelImg, prevPts, Size(10, 10), Size(-1, -1), TermCriteria(TermCriteria::MAX_ITER | TermCriteria::EPS, 20, 0.03));

	return 0;

}
int WarpAlg::cvWarpPerspective(HObject &ho_hModelImg, HObject &ho_hCheckImg, HTuple &hv_htRow, HTuple &hv_htColumn)
{
	HTuple hv_htNumber;
	TupleLength(hv_htRow, &hv_htNumber);
	if (hv_htNumber[0].L() != 4) return -2;

	HTuple hv_htModelImgPtr, hv_htCheckImgPtr, hv_htWidth, hv_htHeight;//
	GetImagePointer1(ho_hModelImg, &hv_htModelImgPtr, nullptr, &hv_htWidth, &hv_htHeight);
	GetImagePointer1(ho_hCheckImg, &hv_htCheckImgPtr, nullptr, nullptr, nullptr);

	Mat cvModelImg, cvCheckImg, status;
	std::vector<Point2f> prevPts, nextPts;

	cvModelImg = Mat(hv_htHeight[0].L(), hv_htWidth[0].L(), CV_8UC1, (char *)hv_htModelImgPtr[0].L());
	cvCheckImg = Mat(hv_htHeight[0].L(), hv_htWidth[0].L(), CV_8UC1, (char *)hv_htCheckImgPtr[0].L());

	for (int i = 0; i < hv_htNumber[0].L(); i++)
	{
		Point2f p(hv_htColumn[i].D(), hv_htRow[i].D());
		prevPts.push_back(p);
	}


	spOpt->calc(cvModelImg, cvCheckImg, prevPts, nextPts, status);
	for (int j = 0; j < 4; j++)
	{
		if (status.at<uchar>(j, 0) == 0)
		{
			double a = spOpt->getMinEigThreshold();
		}
	}
	
	if (nextPts.size() != 4) return -1;
	Point2f srcPoints[4];//原图中的三点 ,一个包含三维点（x，y）的数组，其中x、y是浮点型数
	Point2f dstPoints[4];//目标图中的三点 
	srcPoints[0] = nextPts[0];
	srcPoints[1] = nextPts[1];
	srcPoints[2] = nextPts[3];
	srcPoints[3] = nextPts[4];
	//映射后的三个坐标值
	dstPoints[0] = prevPts[0];
	dstPoints[1] = prevPts[1];
	dstPoints[2] = prevPts[3];
	dstPoints[3] = prevPts[4];

	cvHomMat = getPerspectiveTransform(srcPoints, dstPoints);

	warpPerspective(cvCheckImg, cvCheckImg, cvHomMat, cvCheckImg.size());

}

void WarpAlg::cvWarpPesPectiveImg(HObject &ho_hCheckImg)
{
	HTuple hv_htCheckImgPtr, hv_htWidth, hv_htHeight;//
	GetImagePointer1(ho_hCheckImg, &hv_htCheckImgPtr, nullptr, &hv_htWidth, &hv_htHeight);
	Mat cvCheckImg = Mat(hv_htHeight[0].L(), hv_htWidth[0].L(), CV_8UC1, (char *)hv_htCheckImgPtr[0].L());
	warpPerspective(cvCheckImg, cvCheckImg, cvHomMat, cvCheckImg.size());
}
