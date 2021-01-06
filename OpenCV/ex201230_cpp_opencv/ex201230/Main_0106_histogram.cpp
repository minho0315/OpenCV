#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int ac, char** av) {

	Mat img_1 = imread("Lenna.png", 0);	//�̹����� grayscale�� �ҷ���

	Mat hist_img;

	equalizeHist(img_1, hist_img);//����ȭ�� �̹����� hist_img�� ����

	imshow("Original", img_1);
	imshow("Histogram equalization", hist_img);

	waitKey(0);



	return 0;
}