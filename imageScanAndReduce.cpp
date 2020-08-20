#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

Mat& ScanImageAndReduceC(Mat& srcImage, String imgName, const uchar* const table);

/*int main(int argc, char* argv[]) {
	String imageName = "garden.jpg";
	String imagePath = "Resource/" + imageName;
	Mat image;
	image = imread(imagePath, IMREAD_COLOR); // Read the file
	namedWindow(imageName, WINDOW_AUTOSIZE);
	imshow(imageName, image);

	uchar table[256];
	int divideWith = 100; //像素数值的除数
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(divideWith * (i / divideWith));

	double t = getTickCount();

	Mat imageClone;
	imageClone = ScanImageAndReduceC(image, imageName, table);

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();//计算运算时间
	cout << "Time of reducing with the iterator " << t << " milliseconds." << endl;

	waitKey(0);
	return 0;
}*/

Mat& ScanImageAndReduceC(Mat& srcImage, String imgName, const uchar* const table) {
	Mat imageClone = srcImage.clone();
	int nRows = imageClone.rows;
	int nColumns = imageClone.cols;
	int channels = imageClone.channels();

	/*switch (channels) {
	case 1: { //单通道
		MatIterator_<uchar> it, end;
		for (it = imageClone.begin<uchar>(), end = imageClone.end<uchar>(); it != end; it++) {
			*it = table[*it];
		}
		break;
	}case 3: {//三通道
		MatIterator_<Vec3b> it, end;
		for (it = imageClone.begin<Vec3b>(), end = imageClone.end<Vec3b>(); it != end; it++) {
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
	}
	}*/

	/*uchar* p;
	for (int i = 0; i < nRows; i++) {
		p = imageClone.ptr(i);
		for (int j = 0; j < nColumns * channels; j++) {
			p[j] = table[p[j]];
		}
	}*/

	for (int y = 0; y < nRows; y++) {
		for (int x = 0; x < nColumns; x++) {
			for (int c = 0; c < channels; c++) {
				imageClone.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(table[imageClone.at<Vec3b>(y,x)[c]]);
			}
		}
	}

	imwrite("./images/clone_" + imgName, imageClone);
	namedWindow("clone_" + imgName, WINDOW_AUTOSIZE);
	imshow("clone_" + imgName, imageClone);
	return imageClone;
}