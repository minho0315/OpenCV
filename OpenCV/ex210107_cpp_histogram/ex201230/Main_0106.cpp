#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int ac, char** av) {

	/*이미지 불러오기*/
	Mat img1 = imread("Lenna.png", 1); //자신이 저장시킨 이미지 이름이 입력되어야 함, 확장자까지
	//같은 프로젝트 내에 있다면 "" 안에 상대경로, 아니라면 절대 경로 입력
	//1이라고 적힌 부분은 flag, 1이 default 설정이다.
	//1 = 색정보를 포함에서 불러온다.
	//0=이미지 파일을 흑백으로 변환하여 불러온다.
	//-1=이미지 파일을 색정보와 알파 채널까지 포함하여 불러온다. 
	//reduced 옵션을 사용하면 크기 조절도 가능
	Mat img2 = imread("Lenna.png", 0);
	Mat img3 = imread("Lenna.png", -1);


	imshow("img flag 1", img1); //img를 띄울 윈도우창 타이틀 이름이 "img"
	imshow("img flag 0", img2);
	imshow("img flag -1", img3);
	waitKey(0);//키입력을 기다릴 시간이 0이라는 의미

	/*이미지 색채널 변경*/
	// cvtColor( input Array,  output Array, flag)
	// - input Array를 입력받아 flag 에 대한 옵션으로 이미지 색채널을 변경하여 output Array에 저장한다.
	// - 컬러 색 채널을 다룰 경우 BGR 순이다.
	Mat color_img = imread("Lenna.png");
	Mat grayscale_img;

	cvtColor(color_img, grayscale_img, COLOR_BGR2GRAY);//grayscale로 색채널 변경, 인자를 6으로 줘도 똑같이 동작
	
	imshow("color_img", color_img);
	imshow("grayscale_img", grayscale_img);
	waitKey(0);


	/*이미지 밝기 조절*/
	//OpenCV에서는 각 픽셀의 값들에 대해 최대값255 최소값 0의 범위를 벗어나지 않도록 연산처리를 해준다

	Mat img_2 = img2 + 100; //전체적으로 밝아진다.
	Mat img_3 = img2 - 100; //전체적으로 어두워진다. 100을 뺄셈할 때 최소값 0이 되는 픽셀이 많아 전체적으로 어둡게 느껴진다.
	Mat img_4 = img2 * 2;//밝았던 부분이 훨씬 밝게
	Mat img_5 = img2 / 2;//나눗셈 연산으로 안정적으로 어두워진다.

	imshow("original", img2);
	imshow("img_sum", img_2);
	imshow("img_sub", img_3);
	imshow("img_mul", img_4);
	imshow("img_div", img_5);
	waitKey(0);

	return 0;
}