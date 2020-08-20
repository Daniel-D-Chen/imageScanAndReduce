#include <iostream>
#include <opencv2\core\mat.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

int main/*_filter2D*/(int argc, char* argv[]) {
 	String imgName = "chess2";
	Mat srImg = imread("./Resource/"+ imgName +".jpg",IMREAD_COLOR);
	namedWindow("src_"+imgName,WINDOW_AUTOSIZE);
	imshow("src_" + imgName, srImg);

	/*Mat kernel = (Mat_<float>(3,3)<< 0.0625, 0.125, 0.0625,
									0.125,  0.25,  0.125,
									0.0625, 0.125, 0.0625);//模糊 */

	Mat kernel_h = (Mat_<int>(3, 3) << -1,-2,-1,
									  0, 0, 0,
									  1, 2, 1);//horizon sobel

	Mat kernel_v = (Mat_<int>(3, 3) << -1, 0, 1,
									 -2, 0, 2,
									 -1, 0, 1);//vertical sobel

	/*Mat dst_h,dst_v,dst_sum;
	filter2D(srImg, dst_h, srImg.depth(), kernel_h);
	filter2D(srImg, dst_v, srImg.depth(), kernel_v);
	addWeighted(dst_h ,0.5 ,dst_v , 0.5, 0, dst_sum , -1);*/

	/*Mat kernel = (Mat_<int>(3, 3) << -1, -1, -1,
									   -1,  9, -1,
									   -1, -1, -1); //锐化 */

	double startTime = (double)getTickCount();
	/*Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0,
									 -1, 4, -1,
									 0, -1, 0);//边缘检测(拉普拉斯算子)*/
	Mat dst;
	filter2D(srImg, dst, srImg.depth(), kernel_v);
	namedWindow("dst_" + imgName, WINDOW_AUTOSIZE);
	imshow("dst_" + imgName, dst);
	double millseconds = ((double)(getTickCount() - startTime)) / (getTickFrequency()/1000);
	cout << "使用时间：" << millseconds<<"ms"<<endl;

	startTime = (double)getTickCount();
	Mat kx = (Mat_<int>(1, 3) << 1, 2, 1);
	Mat ky = (Mat_<int>(1, 3) << -1, 0, 1);
	sepFilter2D(srImg, dst, srImg.depth(), kx, ky, Point(-1, -1), 0, BORDER_DEFAULT);
	namedWindow("dst_" + imgName, WINDOW_AUTOSIZE);
	imshow("dst_sepFilter_" + imgName, dst);
	millseconds = ((double)(getTickCount() - startTime)) / (getTickFrequency() / 1000);
	cout << "使用时间：" << millseconds << "ms" << endl;
	ColormapTypes
	waitKey(0);
	return 0;
}