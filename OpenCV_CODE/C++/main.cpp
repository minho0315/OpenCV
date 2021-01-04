// 사진 밝기 조절
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int ac, char** av) {

	Mat img_1 = imread("../Image/ThankYou.jpg", IMREAD_GRAYSCALE);

	Mat img_2 = img_1 + 100; // 밝게
	Mat img_3 = img_1 - 100; // 어둡게

	imshow("original", img_1);
	imshow("img_sum", img_2);
	imshow("img_sub", img_3);

	waitKey(0);

	return 0;
}

////사진 엣지 출력 (단, GRAYSCALE 에서만 가능함. 주의!)
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp> // Canny 함수를 사용하기 위해서 추가함.
//#include <opencv2/videoio.hpp>
//#include <iostream>
//#include <stdio.h>
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	//Mat image = imread("../Image/ThankYou.jpg");
//	Mat image = imread("../Image/ThankYou.jpg", IMREAD_GRAYSCALE);
//
//
//
//	if (image.empty()) // 이미지가 없으면
//	{
//		cout << "이미지가 없습니다." << endl;
//		return -1;
//	}
//
//
//	Canny(image, image, 50, 150); // 주의! IMREAD_GRAYSCALE (흑백출력) 일때만 사용가능함! 안그러면 에러나옴!
//
//
//	imshow("Original", image);
//	
//	waitKey(0); // 윈도우 종료대기 wiatKey(1000) 는 1초 기다린 뒤 꺼짐.
//
//	return 0;
//}


//// 사진크기 설정
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/videoio.hpp>
//#include <iostream>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	Mat image = imread("../Image/ThankYou.jpg");
//
//
//
//	if (image.empty()) // 이미지가 없으면
//	{
//		cout << "이미지가 없습니다." << endl;
//		return -1;
//	}
//
//
//	//namedWindow 는 이미지를 보여줄 윈도우를 생성
//	//namedWindow("Original", WINDOW_AUTOSIZE);
//	namedWindow("Original", WINDOW_NORMAL);
//	// WINDOW_AUTOSIZE 는 이미지크기에 맞게 윈도우 크기가 정해짐.
//	// WINDOW_NORMAL 은 이미지가 큰 경우 해상도 크기에 맞춰 윈도우크기가 조정되고, 사용자가 윈도우 크기를 조정할 수 있음.
//
//
//	//전체화면으로 출력↓
///*	namedWindow("Original", WND_PROP_FULLSCREEN);
//	setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);*/
//	// =======================================================
//
//
//	imshow("Original", image);
//
//	waitKey(0); // 윈도우 종료대기 wiatKey(1000) 는 1초 기다린 뒤 꺼짐.
//
//	return 0;
//}


//// 흑백사진 출력
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/videoio.hpp>
//#include <iostream>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	//Mat image = imread("../Image/ThankYou.jpg");
//	Mat image = imread("../Image/ThankYou.jpg", IMREAD_GRAYSCALE);
//
//
//	if (image.empty()) // 이미지가 없으면
//	{
//		cout << "이미지가 없습니다." << endl;
//		return -1;
//	}
//
//	
//
//
//	imshow("Title", image);
//
//	waitKey(0); // 윈도우 종료대기 wiatKey(1000) 는 1초 기다린 뒤 꺼짐.
//
//	return 0;
//}


//// 이미지 출력
//#include <opencv2/core.hpp> // opencv에서 사용하는 기본적인 자료구조와 함수들이 포함돼있음.
//#include <opencv2/imgcodecs.hpp> // 이미지 파일을 읽어오는 함수와 저장하는 함수를 포함
//#include <opencv2/highgui.hpp> // 인터페이스를 구현해놓은 모듈, 사용자의 입력을 받기위해 대기하는 함수와 화면에 이미지를 보여주기 위한 함수를 포함
//#include <opencv2/videoio.hpp>
//#include <iostream>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	Mat image = imread("../Image/ThankYou.jpg");
//
//
//
//	if (image.empty()) // 이미지가 없으면
//	{
//		cout << "이미지가 없습니다." << endl;
//		return -1;
//	}
//
//	imshow("Title", image);
//
//	waitKey(0); // 윈도우 종료대기 wiatKey(1000) 는 1초 기다린 뒤 꺼짐.
//
//	return 0;
//}