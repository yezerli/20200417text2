#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {


	Mat src = imread("E:\\Git\\0417\\die_on_chip.png", 0);
	Mat disMat;
	threshold(src, disMat, 140, 255, THRESH_BINARY_INV);


	//通过findContours函数寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(disMat, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) {
		//获得最小外界四边形
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = rbox.size.width;
		float height = rbox.size.height;
		float wh_rate = width / height;
		if (wh_rate < 1.1 && wh_rate > 0.9 && width > 20) {
			drawContours(disMat, contours, i, Scalar(0, 255, 255), 1, 8);
			cv::Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; ++i) {
				line(src, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}
	imshow("src", src);
	imshow("disMat", disMat);
	waitKey(0);
	return 0;
}