#include <iostream>
#include <opencv2\core\mat.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
using namespace std;
using namespace cv;


int main2(int argc, char** argv) {
	Mat src = imread("./Resource/Insufficient_brightness.jpg",IMREAD_COLOR);
	String SRC_WINDOW = "srcWindow";
	namedWindow(SRC_WINDOW, WINDOW_AUTOSIZE);
	imshow(SRC_WINDOW, src);

	Mat brighter = src.clone();
	String BRIGHTER_WINDOW = "briWindow";
	Mat lookUpTable = Mat(1, 256, CV_8UC3);
	double gamma = 0.4;
	for (int y = 0; y < lookUpTable.rows; y++) {
		for (int x = 0; x < lookUpTable.cols; x++) {
			for (int c = 0; c < lookUpTable.channels(); c++) {
				if (0==c) {
					lookUpTable.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(pow(x * 3 / 255.0, gamma) * 255.0);
				}else {
					lookUpTable.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(pow(x * 2 / 255.0, gamma) * 255.0);
				}
			}
		}
	}
	/*int channels = brighter.channels();
	for (int i = 0; i < brighter.rows; i++) {
		uchar* p = brighter.ptr(i);
		for (int j = 0; j < brighter.cols * channels; j++) {
			p[j] = saturate_cast<uchar>(pow(p[j]*2.8/255.0, gamma) * 255.0);
		}
	}*/
	LUT(brighter, lookUpTable, brighter);
	namedWindow(BRIGHTER_WINDOW, WINDOW_AUTOSIZE);
	imshow(BRIGHTER_WINDOW, brighter);

	waitKey(0);
	return 0;
}