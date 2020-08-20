#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

static String window_name = "Smoothing Demo";
static Mat src, dst;
static void Smooth(int, void*);//�˲����ú���
static Mat addGaussianNoise(cv::Mat& image);//��Ӹ�˹����
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

    //src = addGaussianNoise(src);//ԭͼ����Ӹ�˹����
    dst = src.clone();
    createTrackbar("�˾�����:\n 0: ��ͨ \n 1: ��˹ \n 2:��ֵ \n 3: ˫��", window_name, &smoothType, smoothSize, Smooth);
    createTrackbar("�˰뾶:\n", window_name, &kernelSize, maxKernelSize, Smooth);
    Smooth(0,0);
    waitKey(0);
    return 0;
}

static void Smooth(int, void*) {
    switch (smoothType) {
        case 0:
            cout << "���˲���" << endl;
            blur(src, dst, Size(kernelSize*2+1, kernelSize*2+1), Point(-1, -1));
            break;
        case 1:
            cout << "��˹�˲���" << endl;
            GaussianBlur(src, dst, Size(kernelSize * 2 + 1, kernelSize * 2 + 1), 0, 0);
            break;
        case 2:
            cout << "��ֵ�˲���" << endl;
            medianBlur(src, dst, kernelSize * 2 + 1);
            break;
        case 3:
            cout << "˫���˲���" << endl;
            bilateralFilter(src, dst, kernelSize, kernelSize * 2, kernelSize / 2);
            break;
    }

    imshow(window_name, dst);
}

static Mat addGaussianNoise(cv::Mat& image) {
    Mat gaussianNoise = Mat::zeros(image.rows, image.cols, image.type());
    RNG rng; //����һ��RNG��
    rng.fill(gaussianNoise, RNG::NORMAL, 10, 20); //������ͨ���ĸ�˹�ֲ������
    image = image + gaussianNoise;
    return image;
}