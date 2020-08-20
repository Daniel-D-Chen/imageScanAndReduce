#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

static String window_name = "Smoothing Demo";
static Mat src, dst;
static void Smooth(int, void*);//滤波调用函数
static Mat addGaussianNoise(cv::Mat& image);//添加高斯噪声
static int smoothType = 0;
static int smoothSize = 3;
static int kernelSize = 0;
static int maxKernelSize = 30;

int main_Smooth(int argc, char** argv) {
    namedWindow(window_name, WINDOW_AUTOSIZE);
    String filename = "lena.jpg";
    src = imread("Resource/" + filename, cv::IMREAD_COLOR);
    if (src.empty())
    {
        cout<<" Error opening image\n";
        cout<<" Usage: \n"<< filename;
        return EXIT_FAILURE;
    }

    //src = addGaussianNoise(src);//原图像添加高斯噪声
    dst = src.clone();
    createTrackbar("滤镜类型:\n 0: 普通 \n 1: 高斯 \n 2:中值 \n 3: 双边", window_name, &smoothType, smoothSize, Smooth);
    createTrackbar("核半径:\n", window_name, &kernelSize, maxKernelSize, Smooth);
    Smooth(0,0);
    waitKey(0);
    return 0;
}

static void Smooth(int, void*) {
    switch (smoothType) {
        case 0:
            cout << "简单滤波！" << endl;
            blur(src, dst, Size(kernelSize*2+1, kernelSize*2+1), Point(-1, -1));
            break;
        case 1:
            cout << "高斯滤波！" << endl;
            GaussianBlur(src, dst, Size(kernelSize * 2 + 1, kernelSize * 2 + 1), 0, 0);
            break;
        case 2:
            cout << "中值滤波！" << endl;
            medianBlur(src, dst, kernelSize * 2 + 1);
            break;
        case 3:
            cout << "双边滤波！" << endl;
            bilateralFilter(src, dst, kernelSize, kernelSize * 2, kernelSize / 2);
            break;
    }

    imshow(window_name, dst);
}

static Mat addGaussianNoise(cv::Mat& image) {
    Mat gaussianNoise = Mat::zeros(image.rows, image.cols, image.type());
    RNG rng; //创建一个RNG类
    rng.fill(gaussianNoise, RNG::NORMAL, 10, 20); //生成三通道的高斯分布随机数
    image = image + gaussianNoise;
    return image;
}