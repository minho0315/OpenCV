#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int ac, char** av) {

	Mat img_1 = imread("Lenna.png", 0);	//이미지를 grayscale로 불러옴

	Mat hist_img;

	equalizeHist(img_1, hist_img);//균일화한 이미지를 hist_img에 저장

	imshow("Original", img_1);
	imshow("Histogram equalization", hist_img);

	waitKey(0);



	return 0;
}